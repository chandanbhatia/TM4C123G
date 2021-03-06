///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Author      : Chandan Bhatia
Device      : Tiva C Series microcontroller TM4C123G
Description : We are using SysTick Module for craeting wait/delay Function which will be multiple of 1 milliseconds.
              We are using 16 MHz precision internal oscillator.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Constant declarations 
#define NVIC_ST_CTRL_R      (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R    (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R   (*((volatile unsigned long *)0xE000E018))


void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}

// The delay parameter is in units of the 16 MHz core clock.
void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // CURRENT value
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}
// 1 milliseconds
void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(16000); 
  }
}

