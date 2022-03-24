#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "DS3231.h"
#include "ATmega328_UART.h"

#define BUTTON_REGISTER DDRC
#define BUTTON_PIN PINC

#define B0 (1 << PC0)    //0
#define B1 (1 << PC1)    //1
#define B2 (1 << PC2)    //2
#define B3 (1 << PC3)    //3

void uart_send(uint8_t * data, uint16_t len);
void uart_print(char * str);
/*uint8_t graph_mode[15]= {0x1B,0x5C,0x3F,0x4C,0x47,0x30,0x3B,0x30,0x3B,0x36,0x34,0x3B,0x36,0x34,0x3B};
uint8_t pic[512]=
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80,
    0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80,
    0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80,
    0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0,
    0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0,
    0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0,
    0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0,
    0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0,
    0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0,
    0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0,
    0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0,
    0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0,
    0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0,
    0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0,
    0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0,
    0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0,
    0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0,
    0x0e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0,
    0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xe0,
    0x0f, 0x78, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xe0,
    0x07, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x7b, 0xc0,
    0x07, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x7b, 0xc0,
    0x07, 0xbe, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xc0,
    0x07, 0x9f, 0x00, 0x00, 0x00, 0x01, 0xf3, 0xc0,
    0xc3, 0x9f, 0x80, 0x00, 0x00, 0x03, 0xe7, 0x86,
    0x63, 0xcf, 0xc0, 0x00, 0x00, 0x07, 0xc7, 0x8c,
    0x7b, 0xc7, 0xe0, 0x00, 0x00, 0x0f, 0xc7, 0xbc,
    0x3f, 0xc3, 0xf0, 0x00, 0x00, 0x1f, 0x8f, 0xf8,
    0x3f, 0xe3, 0xfc, 0x00, 0x00, 0x7f, 0x0f, 0xf8,
    0x1f, 0xe1, 0xff, 0x00, 0x01, 0xfe, 0x1f, 0xf0,
    0x1f, 0xf0, 0xff, 0xe0, 0x0f, 0xfc, 0x1f, 0xf0,
    0x0f, 0xf8, 0x3f, 0xff, 0xff, 0xf8, 0x3f, 0xe0,
    0x07, 0xf8, 0x1f, 0xff, 0xff, 0xf0, 0x7f, 0xc0,
    0x07, 0xfc, 0x0f, 0xff, 0xff, 0xc0, 0xff, 0xc0,
    0x03, 0xfe, 0x03, 0xff, 0xff, 0x00, 0xff, 0x80,
    0x01, 0xff, 0x00, 0x7f, 0xfc, 0x01, 0xff, 0x00,
    0x00, 0xff, 0x80, 0x07, 0xc0, 0x03, 0xfe, 0x00,
    0x00, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xfe, 0x00,
    0x00, 0x7f, 0xf0, 0x00, 0x00, 0x1f, 0xfc, 0x00,
    0x00, 0x3f, 0xf8, 0x00, 0x00, 0x7f, 0xf8, 0x00,
    0x00, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0x00,
    0x03, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0x80,
    0x08, 0x07, 0xff, 0xff, 0xff, 0xff, 0x80, 0x20,
    0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
*/
uint8_t send_reset[4]= {0x1B,0x5C,0x3F,0x52}; //Reset display CPU
//uint8_t nn[2]= {0x81,0x8E}; //Celsius degree sign
uint8_t clear_display[4]= {0x1B,0x5B,0x32,0x4A}; //Clear display
//uint8_t reverse_mode[4]= {0x1B,0x5B,0x37,0x6D}; //Display mode set for reverse mode
uint8_t screen_mode[6]= {0x1B,0x5C,0x3F,0x4C,0x53,0x33}; //Screen Mode
//uint8_t set_virtual_cursor[6]= {0x1B,0x5B,0x31,0x3B,0x36,0x48}; //Set virtual cursor Py=31H Px=36H
uint8_t dispstat=0;
uint8_t setstat=0;
uint8_t sec_set=0;
uint8_t min_set=0;
uint8_t hour_set=12;
uint8_t date_set=1;
uint8_t mon_set=1;
uint8_t year_set=20;
struct DS3231 rtc;
int main(void)
{
    BUTTON_REGISTER &= ~(B0 | B1 | B2 | B3); //Set control pins as inputs
    DS3231_begin();
    UART_Init(UART_CHARACTER_SIZE_8,UART_PARITY_ODD,UART_STOP_BITS_1);
    //Serial.begin(19200, SERIAL_8O1); // 19200 baudrate Parity bit: Odd
    //while (!Serial) { }
    _delay_ms(100);
    uart_send(send_reset, 4);
    _delay_ms(2900);
    cli();
    TCNT1  = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 62499;            // compare match register 16MHz/256/2Hz
    TCCR1B = ((1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10));    // 256
    TIMSK1 = (1 << OCIE1A);
    /*TCNT0  = 0;
    TCCR0A = 0;
    TCCR0B = 0;
    TCCR0A = (1 << WGM01);
    TCCR0B =  (1<<CS00)|(1 << CS02);
    OCR0A = 0xF9;
    TIMSK0 = (1 << OCIE0A);*/
    sei();
   /* uart_send(graph_mode, 15);
    uart_send(pic, 512);*/
    uart_send(screen_mode,6);

    while (1)
    {

    }
    return 0;
}




void uart_send(uint8_t * data, uint16_t len)
{
    uint16_t i = 0;
    while (i < len)
    {
        UART_Putchar(data[i], NULL);
        i++;
    }
}

void uart_print(char * str)
{
    uint16_t i = 0;
    while (str[i] != 0)
    {
        UART_Putchar(str[i], NULL);
        i++;
    }
}

void uart_number(uint8_t number)
{
    char q[] = "xx";
    if (number>99)
    {
        q[0]=48;
        q[1]=48;
    }
    else
    {
        q[0]=((number / 10)+48);
        q[1]=((number % 10)+48);
    }
    uart_print(q);
}

void uart_textset(uint8_t number)
{
  switch (number)
  {
   case 0:
   uart_print("SET hours    ");
   break;
   case 1:
   uart_print("SET minutes  ");
   break;
   case 2:
   uart_print("SET seconds  ");
   break;
   case 3:
   uart_print("SET year     ");
   break;
   case 4:
   uart_print("SET month    ");
   break;
   case 5:
   uart_print("SET date     ");
   break;
   case 6:
   uart_print("Confirm SET  ");
   break;
   case 7:
   uart_print("SET status OK");
   break;
  }

}



uint8_t number_days(uint8_t m, uint16_t y)
	{
		y=y+2000;
		uint16_t leap = (1 - (y % 4 + 2) % (y % 4 + 1)) * ((y % 100 + 2) % (y % 100 + 1)) + (1 - (y % 400 + 2) % (y % 400 + 1));
		return 28 + ((m + (m / 8)) % 2) + 2 % m + ((1 + leap) / m) + (1/m) - (leap/m);
	}


ISR(TIMER1_COMPA_vect)
{
          if (!(PINC&B3))
             {
              if (dispstat<1){dispstat++;}
              else {
                     if (setstat==6)
                        {
                         DS3231_setTime(&rtc, hour_set, min_set, sec_set);
                         DS3231_setDate(&rtc, date_set, mon_set, 2000+year_set);
                         DS3231_setDOW(&rtc);
                         setstat=7;
                        }
                        dispstat=0;
                    }
              uart_send(clear_display,4);
             }
  switch (dispstat)
  {
     case 0 :
             uart_print("\x1b[1;6H");
             uart_print(DS3231_getTimeStr(&rtc,FORMAT_LONG));
             uart_print("\x1b[2;1H");
             uart_print(DS3231_getDateStr(&rtc,FORMAT_LONG,FORMAT_BIGENDIAN,'.'));
             uart_print(" ");
             uart_print(DS3231_getDOWStr(&rtc,FORMAT_LONG));


     break;
     case 1 :
          if (!(PINC&B2))
             {
              if (setstat<6){setstat++;}
              else {setstat=0;}
             }

           switch (setstat)
           {
           case 0:

               if (!(PINC&B0))
                  {
                   if (hour_set<23){hour_set++;}
                   else {hour_set=0;}
                  }

               if (!(PINC&B1))
                  {
                   if (hour_set>0){hour_set--;}
                   else {hour_set=23;}
                  }
           break;
           case 1:
              if (!(PINC&B0))
                 {
                  if (min_set<59){min_set++;}
                  else {min_set=0;}
                 }

               if (!(PINC&B1))
                  {
                   if (min_set>0){min_set--;}
                   else {min_set=59;}
                  }
           break;
           case 2:
              if (!(PINC&B0))
                 {
                  if (sec_set<59){sec_set++;}
                  else {sec_set=0;}
                 }

               if (!(PINC&B1))
                  {
                   if (sec_set>0){sec_set--;}
                   else {sec_set=59;}
                  }
           break;
           case 3:
              if  (!(PINC&B0))
                  {
                   if (year_set<99){year_set++;}
                   else {year_set=0;}
                   if (date_set>number_days(mon_set,year_set)) {date_set=number_days(mon_set,year_set);}
                  }

               if (!(PINC&B1))
                  {
                   if (year_set>0){year_set--;}
                   else {year_set=99;}
                   if (date_set>number_days(mon_set,year_set)) {date_set=number_days(mon_set,year_set);}
                  }
           break;
           case 4:
              if (!(PINC&B0))
                 {
                  if (mon_set<12){mon_set++;}
                  else {mon_set=1;}
                  if (date_set>number_days(mon_set,year_set)) {date_set=number_days(mon_set,year_set);}
                 }

              if (!(PINC&B1))
                 {
                  if (mon_set>1){mon_set--;}
                  else {mon_set=12;}
                  if (date_set>number_days(mon_set,year_set)) {date_set=number_days(mon_set,year_set);}
                 }
           break;
           case 5:
              if (!(PINC&B0))
                 {
                  if (date_set<number_days(mon_set,year_set)){date_set++;}
                  else {date_set=1;}
                 }

              if (!(PINC&B1))
                 {
                   if (date_set>1){date_set--;}
                   else {date_set=number_days(mon_set,year_set);}
                 }
            break;
            }
             uart_print("\x1b[1;1H");
             uart_textset(setstat);
             uart_print("\x1b[2;1H");
             uart_number(hour_set);
             uart_print(":");
             uart_number(min_set);
             uart_print(":");
             uart_number(sec_set);
             uart_print(" ");
             uart_print("20");
             uart_number(year_set);
             uart_print(".");
             uart_number(mon_set);
             uart_print(".");
             uart_number(date_set);
         break;
    }
}
