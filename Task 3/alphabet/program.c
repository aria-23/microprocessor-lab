#include <mega16.h>
#include <alcd.h>

//overflow counter for timer 0
int ov_counter = 0;
//lcd row
int row = 0;
//lcd columns
int column = 0;
//alphabet index
int i = 0;
char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";


interrupt [TIM0_OVF] void timer0_ovf_isr(void){
  ov_counter++;

  if(ov_counter == 700){
    //show alphabet at lcd row and column
    lcd_putchar(alphabet[i]);
    i++;
    //go to next column  
    column++;
    
    //go to next lcd row when lcd shows "m"
    if(column == 13){
      column = 0;
      row = 1;                              
    }
    
    lcd_gotoxy(column, row);
    ov_counter = 0;
    
    //disable interrupt when lcd shows "z"
    if(i == 26){
      TIMSK = 0x00;
    }   
    
  }
}

//lcd configuration on PORTB
//RS = bit 0
//RD = bit 1
//EN = bit 2
//D4 = bit 4
//D5 = bit 5
//D6 = bit 6
//D7 = bit 7

void main(void){
  DDRB=0xFF;
  PORTB=0x00;
  TCCR0=0x01;
  TCNT0=0x00;
  //unmask timer 0 overflow
  TIMSK=0x01;
  //number of lcd columns
  lcd_init(16);
  //enable interrupt
  #asm("sei");
  while (1){
    //do nothing
  }
}