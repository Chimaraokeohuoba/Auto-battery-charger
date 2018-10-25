/* Code by Youngboss
	(c) Copyright Boss-Concepts | 2017
	All Rights Reserved
*/	

/*
Specifications for using this file.

1. The LCD is used in 8bit mode and must be connected to PORTB of the AVR

2. The RS bit of the LCD should be connected to PC7 of the AVR

3. The EN bit of the LCD should be connected to to PC6 of the AVR

4. The RW bit should be connected to the ground.

*/

#define lcd_data PORTB
unsigned char aa,ab,ac,ad,ae,af,ag,ah,ai,aj,ak,al,am,an,ao,ap;
void write_cmd(unsigned char b);
void init_lcd();
void write_data(unsigned char a);
void writestring(unsigned char msg[]);
void init_lcd_scroll();
void lcd_scroll(unsigned char character);
void scroll_msg(unsigned char msg[]);
void writestringXY(int row, int col, unsigned char msg[]);
void scroll_disp();
void write_data(unsigned char a){
	lcd_data=a;
	PORTC|=bit7;
	PORTC|=bit6;
	_delay_ms(1);
	PORTC&=~bit6;
	return;
}void write_cmd(unsigned char b){
	lcd_data = b;
	PORTC&=~bit7;
	PORTC|=bit6;
	_delay_ms(1);
	PORTC&=~bit6;
	return;
}

void BCD_To_ASCII(unsigned char bcd_value, char * p_ascii_text)
{
	//--------------------------------------------------
	// BCD contains digits 0 .. 9 in the binary nibbles
	//--------------------------------------------------
	*p_ascii_text++ = (bcd_value >> 4)  + '0';
	*p_ascii_text++ = (bcd_value & 0x0f) + '0';
	*p_ascii_text = '\0';
	return;
}

void writestring(unsigned char msg[]){
	unsigned char z,v;
	v=strlen(msg);
	for(z=0;z<v;z++){
		write_data(msg[z]);
	}
}

void writeint(int msg){
	char intstr[7];
	itoa(msg,intstr,10);
	writestring(intstr);
}

void writedouble(double msg,int width, int precision){
	char doublestr[7];
	dtostrf(msg, width, precision, doublestr);
	writestring(doublestr);
}

void writebcd(int bcd){
	char bcdstr[10];
	BCD_To_ASCII(bcd, bcdstr);
	writestring(bcdstr);
}

void writestringXY(int row, int col, unsigned char msg[]){
	int position;
	switch(row){
		case 1:
		position = 0x80;
		break;
		case 2:
		position = 0xC0;
		break;
		case 3:
		position = 0x90;
		break;
		case 4:
		position = 0xD0;
		break;
		default:
		position = 0x80;
	}
	position += --col;
	write_cmd(position);
	unsigned char z,v;
	v=strlen(msg);
	for(z=0;z<v;z++){
		write_data(msg[z]);
	}
}

void writeintXY(int row, int col, int msg){
	int position;
	switch(row){
		case 1:
		position = 0x80;
		break;
		case 2:
		position = 0xC0;
		break;
		case 3:
		position = 0x90;
		break;
		case 4:
		position = 0xD0;
		break;
		default:
		position = 0x80;
	}
	position += --col;
	write_cmd(position);
	writeint(msg);
}


void writedoubleXY(int row, int col, double msg, int width, int precision){
	int position;
	switch(row){
		case 1:
		position = 0x80;
		break;
		case 2:
		position = 0xC0;
		break;
		case 3:
		position = 0x90;
		break;
		case 4:
		position = 0xD0;
		break;
		default:
		position = 0x80;
	}
	position += --col;
	write_cmd(position);
	writedouble(msg, width, precision);
}


void writebcdXY(int row, int col, int bcd){
	int position;
	switch(row){
		case 1:
		position = 0x80;
		break;
		case 2:
		position = 0xC0;
		break;
		case 3:
		position = 0x90;
		break;
		case 4:
		position = 0xD0;
		break;
		default:
		position = 0x80;
	}
	position += --col;
	write_cmd(position);
	writebcd(bcd);
}


void blinkCursor(int row, int col){
	int position;
	switch(row){
		case 1:
		position = 0x80;
		break;
		case 2:
		position = 0xC0;
		break;
		case 3:
		position = 0x90;
		break;
		case 4:
		position = 0xD0;
		break;
		default:
		position = 0x80;
	}
	position += --col;
	write_cmd(position);
	write_cmd(0x0F);
}

void init_lcd(){
	write_cmd(0x38);
	write_cmd(0x80);
	write_cmd(0x0C);
}
void clearsc(){
	write_cmd(0x01);
}
void int_lcd_scroll(){
	aa = " ";
	ab = " ";
	ac = " ";
	ad = " ";
	ae = " ";
	af = " ";
	ag = " ";
	ah = " ";
	ai = " ";
	aj = " ";
	ak = " ";
	al = " ";
	am = " ";
	an = " ";
	ao = " ";
	ap = " ";
}
void scroll_disp(){
	write_data(aa);
	_delay_ms(10);
	write_data(ab);
	_delay_ms(10);
	write_data(ac);
	_delay_ms(10);
	write_data(ad);
	_delay_ms(10);
	write_data(ae);
	_delay_ms(10);
	write_data(af);
	_delay_ms(10);
	write_data(ag);
	_delay_ms(10);
	write_data(ah);
	_delay_ms(10);
	write_data(ai);
	_delay_ms(10);
	write_data(aj);
	_delay_ms(10);
	write_data(ak);
	_delay_ms(10);
	write_data(al);
	_delay_ms(10);
	write_data(am);
	_delay_ms(10);
	write_data(an);
	_delay_ms(10);
	write_data(ao);
	_delay_ms(10);
	write_data(ap);
	_delay_ms(10);
}
void lcd_scroll(unsigned char character){
	aa=ab;
	ab=ac;
	ac=ad;
	ad=ae;
	ae=af;
	af=ag;
	ag=ah;
	ah=ai;
	ai=aj;
	aj=ak;
	ak=al;
	al=am;
	am=an;
	an=ao;
	ao=ap;
	ap=character;
	scroll_disp();
}
void scroll_msg(unsigned char msg[]){
	unsigned char z,v;
	v = strlen(msg);
	for (z=0;z<v;z++){
		write_cmd(0x80);
		lcd_scroll(msg[z]);
	}
}