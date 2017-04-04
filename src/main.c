/*
 * main.c
 *
 *  Created on: 29.03.2017
 *      Author: dawid
 */
#define UART_BAUD 56000
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "mycan.h"

#define TOOGLE_DIODE PORTE^=(1<<PE4)

uint8_t uart_buf[20];
uint8_t uart_tx_buf[20];

volatile uint8_t uart_tx_counter;
volatile uint8_t uart_tx_data_size;



volatile uint8_t counter =0;
volatile uint8_t ready_to_send_to_CAN=0;

void USART1_Init (void);
void USART1_Transmit (unsigned char data); 	//Uart pulling transmit
											//for test uses only
void USART1_NB_transmit(uint8_t *data, uint8_t size);//Uart non-blocking transmit

void uart_to_can(); //send via CAN from uart buffer
void check_CAN(); //checking CAN buffers and send via UART if receive something


int main(){

	sei();
	USART1_Init();
	CAN_Init();

	DDRE |= (1<<PE4); //enable blinking diode on board

		while(1){

			if(ready_to_send_to_CAN){
				TOOGLE_DIODE;
				uart_to_can();
				}

			check_CAN();
			}

		return 0;
	}


//Funcions

/********************************************************/
void USART1_Init (void)
{
/* Set baud rate */
	UBRR1H = (unsigned char) (__UBRR>>8);
	UBRR1L = (unsigned char) __UBRR;
	/* Set frame format: 8data, no parity & 1 stop bits */
	UCSR1C = (0<<UMSEL1) |  (3<<UCSZ10);
	/* Enable receiver and transmitte, rx complete interrpt enabler */
	UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<< RXCIE1)| (1<<TXCIE1);
}

/********************************************************/
void USART1_Transmit (unsigned char data)
{
/* Wait for empty transmit buffer */
while ( ! ( UCSR1A & (1<<UDRE1)));
/* Put data into buffer, sends the data */
UDR1 = data;
}
/********************************************************/

void uart_to_can() {

	uint32_t id;
	switch (uart_buf[0]) {

	case TX_A:
		id = uart_buf[1] + ((uint16_t) uart_buf[2] << 8);
		CAN_send_A(0, uart_buf[3], (uint16_t) id, uart_buf + 4);
		ready_to_send_to_CAN = 0;
		break;

	case TX_B:
		id = uart_buf[4] + (uint32_t) (uart_buf[3] << 8)
				+ ((uint32_t) uart_buf[2] << 16)
				+ ((uint32_t) uart_buf[2] << 24);

		CAN_send_B(1, uart_buf[5], id, uart_buf + 6);
		ready_to_send_to_CAN = 0;
		break;

	default:
		ready_to_send_to_CAN = 0;
	}
}
/********************************************************/
void check_CAN() {
	UCSR1B &= ~(1 << RXCIE1); // disable uart interrupt
	uint8_t i = 0;

	CANPAGE &= 0x8;
	CANPAGE |= (14 << MOBNB0);

	if ( CANSTMOB & (1 << RXOK)) {
		if (CANSTMOB & (1 << IDE)) {			// 1 = 2.0B
			uart_tx_buf[0] = RX_B;

			uart_tx_buf[1] = CANIDT4 >> 3;			// id tag
			uart_tx_buf[2] = CANIDT3;
			uart_tx_buf[3] = CANIDT2;
			uart_tx_buf[4] = CANIDT1;

			uart_tx_buf[5] = CANCDMOB & 0x0F; //dlc

			CANPAGE &= 0xF8; //clear indx

			for (i = 0; i < uart_tx_buf[5]; i++) //copy data to buff
				uart_tx_buf[6 + i] = CANMSG;

			USART1_NB_transmit( 6 + uart_tx_buf[5])//send data via uart
		} else { // 2.0A
			uart_tx_buf[0] = RX_A;
			uart_tx_buf[1] = CANIDT2 >> 5; // id tag
			uart_tx_buf[2] = CANIDT1;

			uart_tx_buf[3] = CANCDMOB & 0x0F; //dlc

			CANPAGE &= 0xF8; //clear indx

			for (i = 0; i < uart_tx_buf[3]; i++) //copy data to buff
				uart_tx_buf[4 + i] = CANMSG;

			USART1_NB_transmit( 4 + uart_tx_buf[3])//send data via uart
		}
	}

	UCSR1B |= (1 << RXCIE1); // enable uart interrupt
}
/********************************************************/
void Uart_send_data(uint8_t size){
	uart_tx_data_size = size;
	uart_tx_counter = 1;
	UDR1 = uart_tx_buf[0];
}

void USART1_NB_transmit( uint8_t size){
	// set a size of message and start sending
	uart_tx_data_size = size;
	uart_tx_counter =1;

	UDR1 = uart_tx_buf[0];

}
/********************************************************/
ISR(USART1_TX_vect){

	if(uart_tx_counter){
		if(uart_tx_counter < uart_tx_data_size)
			UDR1 = uart_tx_buf[uart_tx_counter++];
		else
			uart_tx_counter=0;
	}
}

/********************************************************/

ISR(USART1_RX_vect) {

	cli();

	if (counter == 0) {
		uart_buf[0] = UDR1;
		switch (uart_buf[0]) {//check correct of the first byte
		case TX_A:
		case TX_B:
			counter = 1;
			break;

		default:
			break;
		}
	}

	else {
		switch (uart_buf[0]) {//interpret frame according to command
		case TX_A:
			if ((counter > 3)) {
				if (uart_buf[3] > 8)
					counter = 0;
				if (counter > (uart_buf[3] + 2)) {
					uart_buf[counter] = UDR1;//read last data
					counter = 0;
					ready_to_send_to_CAN = 1;// send to can

				} else {
					uart_buf[counter++] = UDR1;
				}

			} else {

				uart_buf[counter++] = UDR1;

			}

			break;
		case TX_B:
			if ((counter > 5)) {
				if (uart_buf[5] > 8)//error detected, abort
					counter = 0;

				if (counter > (uart_buf[5] + 4)) {//is this last data?
					uart_buf[counter] = UDR1;	//read last data
					counter = 0;
					ready_to_send_to_CAN = 1;//send to can

				} else {
					uart_buf[counter++] = UDR1;
				}

			} else {

				uart_buf[counter++] = UDR1;
			}

		}

	}

	sei();
}

ISR(USART1_TX_vect){

	if(uart_tx_counter < uart_tx_data_size)
		UDR1 = uart_tx_buf[uart_tx_counter++];
}












