#include <mega16.h>

//overflow counters
unsigned int ov_counter0 = 0;
unsigned int ov_counter1 = 0;
//7 segment numbers
int sev_seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//4 digits
int ind[] = {0, 0, 0, 0};
//7 segment turn
int sev_seg_turn = 0;

int i = 0;

//timer 1 overflow
interrupt [TIM1_OVF] void timer1_ovf_isr(void){
  ov_counter1++;
  if(ov_counter1 == 20){
    ind[0]++;
    while (i <= 4){
      if( ind[i] == 10){
        ind[i+1]++;
        ind[i] = 0;
      }
     i++;
    }
    i = 0;
    ov_counter1 = 0;
  }
  TCNT1H = 0xFF;
  TCNT1L = 0x00;
}

//timer 0 overflow
interrupt [TIM0_OVF] void timer0_ovf_isr(void){
  ov_counter0++;
  if(ov_counter0 == 3){
    PORTD = sev_seg[ind[3 - sev_seg_turn]];
    if(sev_seg_turn == 0){
    PORTC = 0xFE;
    }
    else{
      PORTC = ((PORTC ^ 0xFF) * 2) ^ 0xFF;
    }
    if(PORTC == 0xEF){
      PORTC = 0xFE;
    }
    ov_counter0 = 0;
    sev_seg_turn++;
    if(sev_seg_turn == 4 ){
      sev_seg_turn = 0;
    }
  }
}

void main(void){
  DDRC = 0xFF;
  DDRD = 0xFF;
  PORTD = 0x00;
  PORTC = 0xFF;
  //prescaler for timer 0
  TCCR0 = 0x05;
  //prescaler for timer 1
  TCCR1B = 0x05;
  TCNT1H=0xFF;
  TCNT1L = 0x00;
  //enable interrputs
  TIMSK = 0x05;
  #asm("sei")
  while (1){
    //do nothing
  }
}
