#include <mega16.h>
#include <delay.h>

void main(void)
{
  DDRB = 0xFF;
  while(1){
    PORTB = PORTA ^ 0x1;
    delay_ms(500); 
  } 
}
