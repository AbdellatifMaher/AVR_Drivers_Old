/*
 * RELAY.h
 *
 * Created: 9/3/2020 9:52:26 PM
 *  Author: 8
 */ 


#ifndef RELAY_H_
#define RELAY_H_

#define  RELAYPORT DIOA
#define  RELAYPIN  PIN0

void RelaySetup(void);
void RelayControl(digitalState state);


#endif /* RELAY_H_ */