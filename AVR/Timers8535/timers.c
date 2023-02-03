/*******************************************************
This program was created by the CodeWizardAVR V3.50 
Automatic Program Generator
© Copyright 1998-2023 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
Version : 
Date    : 02/03/2023
Author  : 
Company : 
Comments: 


Chip type               : ATmega8535
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*******************************************************/

// I/O Registers definitions
#include <mega8535.h>

#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>

int count = 0, ticks = 0;

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
// Place your code here
count++;
if (count == 3) {
	count = 0;
	ticks++;
	if (ticks == 50) {ticks = 0;}
}
}

#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 3
unsigned int adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

// ADC interrupt service routine
// with auto input scanning
interrupt [ADC_INT] void adc_isr(void)
{
static unsigned char input_index=0;
// Read the AD conversion result
adc_data[input_index]=ADCW;
// Select next ADC input
if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT))
   input_index=0;
ADMUX=(FIRST_ADC_INPUT | ADC_VREF_TYPE)+input_index;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
}

// Declare your global variables here
float adc_value[4];


void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 15.625 kHz
// Mode: CTC top=OCR0
// OC0 output: Disconnected
// Timer Period: 16 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0xF9;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<WGM20) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

// ADC initialization
// ADC Clock frequency: 500.000 kHz
// ADC Voltage Reference: AVCC pin
// ADC High Speed Mode: Off
// ADC Auto Trigger Source: Free Running
ADMUX=FIRST_ADC_INPUT | ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (0<<ADIF) | (1<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
SFIOR=(1<<ADHSM) | (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS: PORTB Bit 0
// RD: PORTB Bit 1
// EN: PORTB Bit 2
// D4: PORTB Bit 4
// D5: PORTB Bit 5
// D6: PORTB Bit 6
// D7: PORTB Bit 7
// Characters/line: 40
lcd_init(40);
lcd_init(20);
lcd_init(20);
lcd_gotoxy(0,0);
lcd_puts("Hello");
lcd_gotoxy(0,1);
lcd_putchar(0x32);
lcd_clear();
// Globally enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
	  lcd_gotoxy(0,1);
	  lcd_putchar((adc_data[0]/1000)+0x30);
	  lcd_gotoxy(1,1);
	  lcd_putchar((adc_data[0]%1000)/100+0x30);
	  lcd_gotoxy(2,1);
	  lcd_putchar((adc_data[0]%1000)%100/10+0x30);
	  lcd_gotoxy(3,1);
	  lcd_putchar((adc_data[0]%1000)%100%10+0x30);
	  
	  lcd_gotoxy(6,1);
	  lcd_putchar((adc_data[1]/1000)+0x30);
	  lcd_gotoxy(7,1);
	  lcd_putchar((adc_data[1]%1000)/100+0x30);
	  lcd_gotoxy(8,1);
	  lcd_putchar((adc_data[1]%1000)%100/10+0x30);
	  lcd_gotoxy(9,1);
	  lcd_putchar((adc_data[1]%1000)%100%10+0x30);
	  
	  lcd_gotoxy(0,3);
	  lcd_putchar((adc_data[2]/1000)+0x30);
	  lcd_gotoxy(1,3);
	  lcd_putchar((adc_data[2]%1000)/100+0x30);
	  lcd_gotoxy(2,3);
	  lcd_putchar((adc_data[2]%1000)%100/10+0x30);
	  lcd_gotoxy(3,3);
	  lcd_putchar((adc_data[2]%1000)%100%10+0x30);
	  
	  lcd_gotoxy(6,3);
	  lcd_putchar((adc_data[3]/1000)+0x30);
	  lcd_gotoxy(7,3);
	  lcd_putchar((adc_data[3]%1000)/100+0x30);
	  lcd_gotoxy(8,3);
	  lcd_putchar((adc_data[3]%1000)%100/10+0x30);
	  lcd_gotoxy(9,3);
	  lcd_putchar((adc_data[3]%1000)%100%10+0x30);
	  
	  adc_value[0] = (float)adc_data[0]*5000/1023;
	  lcd_gotoxy(0,0);
	  lcd_putchar(((int)adc_value[0]/1000)+0x30);
	  lcd_gotoxy(1,0);
	  lcd_putchar(((int)adc_value[0]%1000)/100+0x30);
	  lcd_gotoxy(2,0);
	  lcd_putchar(((int)adc_value[0]%1000)%100/10+0x30);
	  lcd_gotoxy(3,0);
	  lcd_putchar(((int)adc_value[0]%1000)%100%10+0x30);
	  
	  adc_value[1] = (float)adc_data[1]*5000/1023;
	  lcd_gotoxy(6,0);
	  lcd_putchar(((int)adc_value[1]/1000)+0x30);
	  lcd_gotoxy(7,0);
	  lcd_putchar(((int)adc_value[1]%1000)/100+0x30);
	  lcd_gotoxy(8,0);
	  lcd_putchar(((int)adc_value[1]%1000)%100/10+0x30);
	  lcd_gotoxy(9,0);
	  lcd_putchar(((int)adc_value[1]%1000)%100%10+0x30);
	  
	  lcd_gotoxy(15,0);
	  lcd_putchar((ticks/10)+0x30);
	  lcd_gotoxy(16,0);
	  lcd_putchar((ticks%10)+0x30);
      }
}
