#ifndef MYCAN_H_
#define MYCAN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#define TX_A 1
#define TX_B 2
#define RX_A 3
#define RX_B 4

void CAN_Init(void);

//this is test only function
void CAN_Send_simple_data(uint8_t mob_number, uint8_t dlc , uint16_t ID, uint8_t* data);





//use these two to send data 2.0A and 2.0B formats
void CAN_send_A(uint8_t dlc , uint16_t ID, uint8_t* data);
void CAN_send_B(uint8_t dlc , uint32_t ID, uint8_t* data);


#endif
