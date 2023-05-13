/*
 * EEPROM_driver.h
 *
 * Created: 20/09/2021 2:16:57 AM
 *  Author: kamar salah
 */ 


#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

/*function description:
write data on given address
*/
void EEPROM_vwrite (unsigned short address, unsigned char data);

/* function description:
read data which in given address
*/
void EEPROM_vread (unsigned short address);

#endif /* EEPROM_DRIVER_H_ */