#include <mega16.h>
#include <delay.h>
void main(void){
  DDRB = 0xFF;
  DDRA = 0x00;
  PORTB = 0x00;
  while(1){
    if(PINA == 0x01){
      int temp = 0x01;
      while(PORTB < 0x80){
        PORTB = temp;
        temp = temp * 2;
        delay_ms(500);
      }
      while(PORTB > 0x00){
        PORTB = PORTB / 2;
        delay_ms(500);
      }
      delay_ms(500);
      PORTB = 0x00; 
    }
  } 
}
