/*
 * Automatic_battery_charger.c
 *
 * Created: 2/8/2018 8:28:07 PM
 *  Author: Youngboss
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "bits.h"
#include "adc.h"
#include "lcd.h"

double Vmax = 18.62;
double Vref = 5.00;
double voltage;
double fullVoltage = 14.50;
double lowBattery = 10.00;
int isCharging = 0;
int isDown = 0;



int main(void)
{
	DDRD = 0xFF;
	DDRB = 0x00;
	DDRC |= bit7;
	DDRC |= bit6;
	ADC_init();

    while(1)
    {
		PORTD &= ~bit1;
		PORTD &= ~bit2;
		_delay_ms(1000);
		checkVoltage();
		if (voltage > 9.01)
		{
			if (voltage == fullVoltage || voltage > fullVoltage)
			{
				stopCharging();
				_delay_ms(5000); //delay for 5 seconds
				if (voltage < (fullVoltage - 1))
				{
					/* subtract the float voltage and check the actual battery voltage, if the battery voltage difference is greater than 1,
					 * restart the charging
					*/
					startCharging();
					PORTD |= bit0;
					
				}else{
					//if the charging voltage minus the float voltage is within a difference of 1, stop the charging
					stopCharging();
					PORTD |= bit0;
				}
			}else{
				startCharging();
			}
		}else{
				startCharging(); // start charging
				shutdown(); //shutdown the inverter;
			
		}
		if (isCharging && (voltage > lowBattery))
		{
			PORTD &= ~bit0;
			PORTD |= bit1;
			_delay_ms(1000);
		}
		if (voltage <= lowBattery)
		{
			PORTD |=bit2; //blink the warning LED for low battery
			_delay_ms(1000); // delay for 1 second
		}
					
		    
    }
}

 void checkVoltage(){
	voltage = ((Vref/1024)*getADC())*(Vmax/Vref); // calculate for voltage
}
void startCharging(){
	PORTD |= bit3; // set the bit3 of PORTD
	isCharging = 1; // set the charging variable to true
}
void stopCharging(){
	PORTD &= ~bit3; // clear the bit3 of PORTD
	isCharging = 0; // set the charging variable to false
}
void shutdown(){
	PORTD |= bit4; // set the bit4 of PORTD
	isDown = 1;
	
}
