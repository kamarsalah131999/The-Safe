/*
 * EEPROM_driver.c
 *
 * Created: 20/09/2021 2:16:34 AM
 *  Author: kamar salah
 */ 

#include <avr/io.h>
#include "macros.h"

void EEPROM_vwrite (unsigned short address, unsigned char data)
{
	/*set up adress register 
	  EEAR=adress  the same next 
	*/
	
	EEARH= (char) address;             // store high 8 bit
	EEARL= (char)(address>>8);        // store law 8 bit
	
	/* set up data register */
	SET_BIT(EECR,EEMWE);             // EEMWE=1 as indecate to start write & EEMWE reblse with pin number
	SET_BIT(EECR,EEWE);              // EEWE=1 as indecate to start write  & EEWE reblse with pin number
	
	/* wait for complitation of write operation by check on EEWE if =1 is inducate the operation
	  dont complete and vice versa
	*/
	while (READ_BIT(EECR,EEWE)==1);
	
}

void EEPROM_vread (unsigned short address)
{
	/*set up adress witch read data on it */
	EEARH= (char) (address);             // store high 8 bit
	EEARL= (char)(address>>8);        // store law 8 bit
	
	/* set EECR to read data */
	SET_BIT(EECR,EERE);
	
	/* return data from data register */
	
    return EEDR;
	
}