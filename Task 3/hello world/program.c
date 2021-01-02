#include <mega16.h>
#include <alcd.h>

//lcd configuration on PORTB
//RS = bit 0
//RD = bit 1
//EN = bit 2
//D4 = bit 4
//D5 = bit 5
//D6 = bit 6
//D7 = bit 7

void main(void){
  DDRB = 0xFF;
  PORTB = 0x00;
  
  //number of lcd lines  
  lcd_init(11);
  
  while (1){
    lcd_gotoxy(0, 0);
    lcd_putsf("Hello World");
  }
}
