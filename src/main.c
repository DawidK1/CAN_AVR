/*
  * main.c
 *
 *  Created on: 29.03.2017
 *      Author: dawid
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "mycan.h"


#define UART_BAUD 500000
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)

#define TX_BUFFER_SIZE 120
#define RX_BUFFER_SIZE 60

#define MAX_READS_FROM_RX 50 //Max number of bytes to read from RX buffer at one cycle


#define TOOGLE_DIODE PORTE^=(1<<PE4)
#define DIODE_ON PORTE &=~ (1<<PE4)
#define DIODE_OFF PORTE |= (1<<PE4)


uint8_t tx_frame_holder[20];


uint8_t tx_buffer[TX_BUFFER_SIZE];
uint8_t *tx_begin_ptr;
uint8_t *tx_end_ptr;
uint8_t tx_frame_holder[20];
volatile uint8_t tx_queue_size;
volatile uint8_t tx_busy;


uint8_t rx_buffer[RX_BUFFER_SIZE];
uint8_t *rx_begin_ptr;
uint8_t *rx_end_ptr;
uint8_t frame_holder[15];
volatile uint8_t rx_queue_size;

volatile uint8_t uart_tx_counter;
volatile uint8_t uart_tx_data_size;


uint8_t counter =0;
uint8_t read_cycles=0;

void USART1_Init (void);
void USART1_Transmit (unsigned char data); 	//Uart polling transmit
											//for test uses only

void add_to_tx_queue(uint8_t *data, uint8_t size);// add data to sending UART buffer
void read_rx_buffer();//read data from buffer and pack them into CAN frames
void uart_to_can(); //send via CAN from uart buffer
void check_CAN(); //checking CAN buffers and send via UART if receive something

inline void get_from_RX_queue(uint8_t* address){// take data from RX buffer
	*address = *rx_begin_ptr;
	++rx_begin_ptr;
	--rx_queue_size;
	if (rx_begin_ptr > rx_buffer + RX_BUFFER_SIZE - 1)
		rx_begin_ptr = rx_buffer;

}

int main(){

	DDRE |= (1<<PE4); //enable blinking diode on board
	DIODE_OFF;

	sei();
	USART1_Init();
	CAN_Init();


		while(1){

			if( ( rx_queue_size > RX_BUFFER_SIZE ) || (tx_queue_size > TX_BUFFER_SIZE ) )// check buffers overload
				DIODE_ON;
			else
				DIODE_OFF;

			check_CAN();
			read_rx_buffer();
			}

		return 0;
	}


/*** __________Functions__________________*/

/********************************************************/
void USART1_Init (void)
{
/* Set baud rate */

	tx_begin_ptr = tx_buffer;// init queues pointers
	tx_end_ptr = tx_buffer;

	rx_begin_ptr = rx_buffer;
	rx_end_ptr = rx_buffer;

	UBRR1H = (unsigned char) (__UBRR>>8);
	UBRR1L = (unsigned char) __UBRR;
	/* Set frame format: 8data, no parity & 1 stop bits */
	UCSR1C = (0<<UMSEL1) |  (3<<UCSZ10);
	/* Enable receiver and transmitte, rx and tx complete interrpt enable */
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
	switch (frame_holder[0]) {

	case TX_A:
		id = frame_holder[1] + ((uint16_t) frame_holder[2] << 8);
		CAN_send_A( frame_holder[3], (uint16_t) id, frame_holder + 4);
		break;

	case TX_B:
		id = frame_holder[4] + (uint32_t) (frame_holder[3] << 8)
				+ ((uint32_t) frame_holder[2] << 16)
				+ ((uint32_t) frame_holder[1] << 24);

		CAN_send_B( frame_holder[5], id, frame_holder + 6);
		break;

	default:
		;
	}
}
/********************************************************/
void check_CAN() {


	uint8_t i = 0;
	uint8_t j = 0;

	for( ; j < 7; j++){
	if (!(CANEN1 & (1 << j))) {//check all MO blocks for message reception hit

			CANPAGE &= 0x8;
			CANPAGE |= ((8 + j) << MOBNB0);

		if (CANCDMOB & (1 << IDE)) {			// 1 = 2.0B

			tx_frame_holder[0] = RX_B;

			tx_frame_holder[1] = CANIDT4 >> 3;			// id tag
			tx_frame_holder[2] = CANIDT3;
			tx_frame_holder[3] = CANIDT2;
			tx_frame_holder[4] = CANIDT1;

			tx_frame_holder[5] = CANCDMOB & 0x0F; //dlc

			CANPAGE &= 0xF8; //clear indx

			for (i = 0; i < tx_frame_holder[5]; i++) //copy data to buff
				tx_frame_holder[6 + i] = CANMSG;

			tx_frame_holder[6 + tx_frame_holder[5]]= 170; //EOF

			//USART1_NB_transmit( 6 + tx_frame_holder[5]  + 1);//send data via uart
			add_to_tx_queue(tx_frame_holder,7 + tx_frame_holder[5] );//add to UART sending buff


		} else { // 2.0A

			tx_frame_holder[0] = RX_A;
			tx_frame_holder[1] = CANIDT2 >> 5; // id tag
			tx_frame_holder[2] = CANIDT1;

			tx_frame_holder[3] = CANCDMOB & 0x0F; //dlc

			CANPAGE &= 0xF8; //clear indx

			for (i = 0; i < tx_frame_holder[3]; i++) //copy data to buff
				tx_frame_holder[4 + i] = CANMSG;

			//USART1_NB_transmit( 4 + tx_frame_holder[3]);//send data via uart

			tx_frame_holder[4+ tx_frame_holder[3] ] = 173;//EOF
			add_to_tx_queue(tx_frame_holder,5 + tx_frame_holder[3]);
		}
		CANIDM1 = 0x00;   	// Clear Mask, let all IDs pass
		CANIDM2 = 0x00;
		CANIDM3 = 0x00;
		CANIDM4 = 0x00;
		CANCDMOB = ( 1 << CONMOB1) | ( 1 << IDE ) | ( 8 << DLC0);  // Enable Reception 29 bit IDE DLC8
		CANGCON |= ( 1 << ENASTB );			// Enable mode. CAN channel enters in enable mode once 11 recessive bits have been read
		CANSTMOB &=~ ( 1 << RXOK);
		}
	}
	}
/********************************************************/
void Uart_send_data(uint8_t size){
	uart_tx_data_size = size;
	uart_tx_counter = 1;
	UDR1 = tx_frame_holder[0];
}
/*****************************************************/
void add_to_tx_queue(uint8_t *data, uint8_t size){
	static uint8_t i =0;

	for (i = 0 ; i < size ; i++){
		*tx_end_ptr = data[i];
		tx_end_ptr++;
		tx_queue_size++;
		if(tx_end_ptr > tx_buffer + TX_BUFFER_SIZE - 1)
			tx_end_ptr = tx_buffer;
	}
	if(!tx_busy){
		UDR1 = *tx_begin_ptr;
		++tx_begin_ptr;
		--tx_queue_size;

		if(tx_begin_ptr > tx_buffer + TX_BUFFER_SIZE - 1)
			tx_begin_ptr = tx_buffer;
	}






}
/******************************************************/
void read_rx_buffer() {

	read_cycles = MAX_READS_FROM_RX;

	while (rx_queue_size && read_cycles ) {

		if (!counter) {
			get_from_RX_queue(frame_holder);
			counter++;
		} else {


			switch (frame_holder[0]) {	//interpret frame according to command
			case TX_A:
				if ((counter > 3)) {
					if (frame_holder[3] > 8)
						counter = 0;

					if (counter > (frame_holder[3] + 2)) {
						get_from_RX_queue(frame_holder + counter);	//read last data

						counter = 0;
						uart_to_can();			// send to can

					} else {
						get_from_RX_queue(frame_holder + counter);
						counter++;

					}

				} else {

					get_from_RX_queue(frame_holder + counter);
					counter++;

				}

				break;

			case TX_B:




				if ((counter > 5)) {



					if (frame_holder[5] > 8)			//error detected, abort
						counter = 0;

					if (counter > (frame_holder[5] + 4)) {	//is this last data?
						get_from_RX_queue(frame_holder + counter);


						counter = 0;

						uart_to_can();	//send to can


					} else {
						get_from_RX_queue(frame_holder + counter);
						counter++;

					}

				} else {

					get_from_RX_queue(frame_holder + counter);
					counter++;

				}
				break;
			default:
				counter = 0;

				break;
			}
		}
	--read_cycles;
	}

}


/*** _______________INTERRUPTS_____________ ***/
/*----------------------------------------------------------*/


ISR(USART1_RX_vect){//New RX interrupt, copy data to queue

    *rx_end_ptr = UDR1;
	++rx_end_ptr;
	++rx_queue_size;
	if(rx_end_ptr > rx_buffer + RX_BUFFER_SIZE - 1){
		rx_end_ptr = rx_buffer;
	}

}

ISR(USART1_TX_vect){//New TX interrupt, which take data from tx_queue
	if(tx_queue_size){
		UDR1 = *tx_begin_ptr;
		--tx_queue_size;
		++tx_begin_ptr;

		if(tx_begin_ptr > tx_buffer + TX_BUFFER_SIZE - 1)
			tx_begin_ptr = tx_buffer;
	}
	else
		tx_busy=0;

}







