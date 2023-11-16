/*
 * MACROS.h
 *
 * Created: 6/9/2020 2:56:26 PM
 *  Author: Abdellatif
 */ 


#ifndef MACROS_H_
#define MACROS_H_

	#define SETBIT(R,B)			((R) |= (1<<(B)))
	#define CLEARBIT(R,B)		((R) &=~(1<<(B)))
	#define TOGGLEBIT(R,B)		((R) ^= (1<<(B)))
	#define READBIT(R,B)		(((R) & (1<<(B)))>>(B))



#endif /* MACROS_H_ */