/*
 * KEYPAD.h
 *
 * Created: 8/15/2020 9:48:05 PM
 *  Author: 8
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define ROWS 4
#define COLS 4

void Key_Configure(DIO *PAD);
vuint8_t Key_PRESSED(DIO *PAD);





#endif /* KEYPAD_H_ */