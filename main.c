/*
 * the safe.c
 * keybad connected internal pullup and LCD conected eight bit mode
 * Created: 13/10/2021 12:23:54 AM
 * Author : kamar salah
 */ 
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "Keybad driver.h"
#include "LCD driver.h"
#define EEPROM_STATUS_LOCATION 0X20                               // this location indicate is the frist time open the safe (0xff) or not (0x00)
#define EEPROM_PASSWARD_LOCATION1 0x21                            // set passward from 4 digit 
#define EEPROM_PASSWARD_LOCATION2 0x22
#define EEPROM_PASSWARD_LOCATION3 0x23
#define EEPROM_PASSWARD_LOCATION4 0x24
#define MAX_TRIES 3



char arr[4];

int main(void)
{
	char value=NOTBRESSED;                                   // value = oxff the default of EEPROM (not programing) 
	char flag=0,i;
	char tries=MAX_TRIES;
	
	
	Keybad_vinit();
	LCD_vinit();
	
	/*set passward  >> this happen at frist time open the safe */
	if ( EEPROM_vread (EEPROM_STATUS_LOCATION)== NOTBRESSED)
	{
		LCD_vsend_sring("set pass:");
		for (i=0; i<4; i++)
		{
			do
			{
				value= Keybad_u8check_press();
				
			} while (value==NOTBRESSED);
			
			LCD_vsend_char(value);
			_delay_ms(500);
			LCD_vmove_cursor(1,10+i);
			LCD_vsend_char('*');
			_delay_ms(500);
			EEPROM_vwrite(EEPROM_PASSWARD_LOCATION1+i,value);                                            // write frist digit from passward in EEPROM
		}
		EEPROM_vwrite(EEPROM_STATUS_LOCATION,0x00);                                                    // location which have passward become programed
	}
	
	/*check passward >> this happen every time open the safe*/
	while (flag==0)
	{
		arr[0]=arr[1]=arr[2]=arr[3]=NOTBRESSED;
		LCD_vclear_screen();
		LCD_vsend_sring ("check pass:") ;
		for (i=0; i<4; i++)
		{
			do
			{
				arr[i]= Keybad_u8check_press();
				
			} while (arr[i]==NOTBRESSED);
			
			LCD_vsend_char(arr[i]);
			_delay_ms(500);
			LCD_vmove_cursor(1,12+i);
			LCD_vsend_char('*');
			_delay_ms(500);
		}
		
		if ((EEPROM_vread (EEPROM_PASSWARD_LOCATION1)== arr[0]) && (EEPROM_vread (EEPROM_PASSWARD_LOCATION2)== arr[1]) && (EEPROM_vread (EEPROM_PASSWARD_LOCATION3)== arr[2]) && (EEPROM_vread (EEPROM_PASSWARD_LOCATION4)== arr[3]))
		{
			LCD_vclear_screen();
			LCD_vsend_sring("right passward");
			LCD_vmove_cursor(2,1);
			LCD_vsend_sring(" the safe opend");
			flag =1;
		}
		else
		{
			tries=tries-1;
			
			if (tries>0)
			{
				LCD_vclear_screen();
				LCD_vsend_sring ("wrong passward");
				_delay_ms(1000);
				LCD_vclear_screen();
				LCD_vsend_sring ("tries left is:");
				LCD_vsend_char (tries+48);
				_delay_ms(1000);
			}
			
			else
			{
				LCD_vclear_screen();
				LCD_vsend_sring ("wrong passward");
				LCD_vmove_cursor (2,1);
				LCD_vsend_sring ("the safe closed ");
				flag=1;
			}
			
		}
		
	}
}
