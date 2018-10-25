/* Code by Youngboss
	(c) Copyright Boss-Concepts | 2017
	All Rights Reserved
*/


/*
To use this header file, the instructions and specifications are written below.

1. The reference voltage for the ADC should be set with the AREF pin of the Avr
(in our case, I used Atmega32 and the AREF pin is pin 32.)

2. Connect the AVCC pin of the of the AVR to the positive power rail.
(in our case, I used Atmega32 and the AVCC pin is pin 30).

3. Connect the AGND pin of the AVR to the negative power rail (Ground)
(in our case, I used Atmega32 and the AGND pin is pin 31).
 
4. Supply the analog voltage to be converted to the ADC channel 0.
(in our case, I used Atmega32. The ADC channels are in PORTA, and the channel 0 is in PA0. pin40 of Atmega32)

5. Optionally, 104 pico farad capacitor might be connected from the AVCC to Ground, in order to reduce noise.

*/


void ADC_init(){
	//call this method first to initialize the inbuilt ADC of the Avr
	ADCSRA=0x87;
	ADMUX=0x00;
}

uint16_t getADC(){
	// call this method anytime you want to get the ADC value
	ADCSRA|=bit6;
	while(!(ADCSRA & (1<<ADIF)));
	return ADC;
}