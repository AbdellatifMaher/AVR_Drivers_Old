/*
 * _7_SEGMENT.h
 *
 * Created: 6/10/2020 4:54:56 PM
 *  Author: 8
 */ 


#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_
	
	#include "GPIO_ATmega32A.h"
	#include "StdTypes.h"
	#include "uc_Configuration.h"

 void Segment_Configure(DIO *dio);
 void Segment_display(DIO *dio,vuint8_t Number);



#endif /* 7_SEGMENT_H_ */