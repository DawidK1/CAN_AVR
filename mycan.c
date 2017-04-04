#include "mycan.h"







////////////////////////////////////////////////////////
void CAN_Init(void){


	CANGCON |= (1<< ENASTB ) // Set CAN enable
			| (1<< TTC) //TTC mode en
			| (1<< SYNTTC)// ttc timer caught on the last bit of the eof (TTC SYNCHRO)
			| (0 << LISTEN); // No Listening mode

	CANGIE |= (1 << ENIT) //En CAN interrupts
			| (1 << ENRX) //En Receive interrupt
			| (1 << ENTX) // En transmitt interrupt
			| (0 << ENERR)// En MOb Error interrupt
			| (0 << ENBX) // En Frame Buffer interrupt
			| (0 <<ENERG) // En Genereal Errors Interrupt
			| (0 << ENOVRT); // En CAN timer overrun interrupt

	CANIE1 |= (1 << IEMOB14);// Used to enable MOb interrupts 14:8
	CANIE2 |= (1 << IEMOB0);// MOb interrupts for 7:0


//	CANBT1 |= (1 << BRP0) //CAN Baud rate prescaller
//			| (1 << BRP1)
//			| (1 << BRP2)
//			| (1 << BRP3)
//			| (1 << BRP4)
//			| (1 << BRP5);
//
//	CANBT2 |= (0 << SJW1)// Re-synchro Jump widith
//			| (1 << SJW0)
//
//			| (1 << PRS2)// Set propagation time
//			| (1 << PRS1)
//			| (1 << PRS0);
//
//	CANBT3 |= (0 << PHS22)// Compensate phase-edge errors
//			| (0 << PHS21)
//			| (0 << PHS20)
//
//			| (0 << PHS12)// Compensate phase-edge errors  ;__;
//			| (0 << PHS11)
//			| (0 << PHS10)
//
//			| (0 << SMP); // sample points per bit


	//CANBT1 = 0x02 ; CANBT2 = 0x0C ; CANBT3 = 0X37;// 500 Kbps
	CANBT1 = 0x12 ; CANBT2 = 0x0C ; CANBT3 = 0X37;// 100 Kbps

	CANTCON = 0; //Can timer prescaller 0-255

	//CANHPMOB 7:4 number of highest priority Mob
	// 3:0 CAN General Purpose bits ??????????

//	CANPAGE |= (1 << MOBNB0)// Choose MOb number 0-14
//			| (0 << AINC) // Auto increment MOb number (active 0)
//			| (0 << INDX0);// Byte location of the CAN data byte into the FIFO for the defined MOb. (0-7)


	//RECEIVE CONFIG
	CANPAGE &=0x08;// clear CANPAGE


	CANPAGE |= (14 << MOBNB0);//choose mob to receive

	CANIDM4 &=~  (1 << IDEMSK);// disable mask, accept all messages

	CANCDMOB|= (1 << CONMOB1);//enable receive
	CANCDMOB &=~ (1 << CONMOB0);

}
//////////////////////////////////////////////////////////


void CAN_Send_simple_data(uint8_t mob_number, uint8_t dlc , uint16_t ID, uint8_t* data){

	uint8_t i=0;
	// Choose MOb

	CANPAGE &= 0x0F;//clear MOb number
	CANPAGE |= (mob_number << MOBNB0);

	// set DLC number
	CANCDMOB &= 0xF0; // clear dlc number
	CANCDMOB |= dlc;

	CANPAGE &= 0xF8;// clear indx

	//set ID tag
	CANIDT1 = (uint8_t)(ID>>3);
	CANIDT2 = (uint8_t)(ID<<5);

	//CANIDT4 &=~ (1 << RTRTAG);

	for(i = 0 ; i < dlc ; i++){
		CANMSG = *(data + i);
		CANPAGE++;


	}
	//CANPAGE &= 0xF8;// clear indx

	CANCDMOB |= (1 << CONMOB0);
	CANCDMOB &=~ ((1 << CONMOB1) | (1 << IDE));// enable trnasmit, 2.0A ver

}
////////////////////////////////////////////////
void CAN_send_A(uint8_t mob_number, uint8_t dlc , uint16_t ID, uint8_t* data){

	uint8_t i=0;
	// Choose MOb

	CANPAGE &= 0x0F;//clear MOb number
	CANPAGE |= (mob_number << MOBNB0);

	// set DLC number
	CANCDMOB &= 0x11110000; // clear dlc number
	CANCDMOB |= dlc;

	CANPAGE &= 0b11111000;// clear indx

	//set ID tag
	CANIDT1 = (uint8_t)(ID>>3);
	CANIDT2 = (uint8_t)(ID<<5);

	CANIDT4 &=~ (1 << RTRTAG);

	for(i = 0 ; i < dlc ; i++){
		CANMSG = data[i];

	}
	CANPAGE &= 0b11111000;

	CANCDMOB |= (1 << CONMOB0);
	CANCDMOB &=~ ((1 << CONMOB1) | (1 << IDE));// enable trnasmit, 2.0A ver



}

void CAN_send_B(uint8_t mob_number, uint8_t dlc , uint32_t ID, uint8_t* data){

	uint8_t i=0;
	// Choose MOb

	CANPAGE &= 0x0F;//clear MOb number
	CANPAGE |= (mob_number << MOBNB0);

	// set DLC number
	CANCDMOB &= 0x11110000; // clear dlc number
	CANCDMOB |= dlc;

	CANPAGE &= 0b11111000;// clear indx

	//set ID tag
	CANIDT1 = (uint8_t)(ID >> 21);
	CANIDT2 = (uint8_t)(ID >> 13);
	CANIDT3 = (uint8_t)(ID >> 5);
	CANIDT4 = (uint8_t)(ID << 3);

	CANIDT4 &= 0xF8;

	CANIDT4 &=~ (1 << RTRTAG);

	for(i = 0 ; i < dlc ; i++){
		CANMSG = data[i];

	}
	CANPAGE &= 0b11111000;

	CANCDMOB |= (1 << CONMOB0)	| (1 << IDE);

	CANCDMOB &=~ ((1 << CONMOB1) | (0 << IDE));// enable trnasmit, 2.0B ver


}
