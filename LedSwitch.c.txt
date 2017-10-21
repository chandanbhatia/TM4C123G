///////////////////////////////////////////////////////////////////////////////////////////////////
/*
Author      : Chandan Bhatia
Device      : Tiva C Series microcontroller TM4C123G
Description : Pogramme in C to toggle an LED when a swittch is pressed and turn the LED on when the
              switch is released. 
	      Swich is connected at PF4 and Green LED is connected at PF3.              
*/
///////////////////////////////////////////////////////////////////////////////////////////////////

//Constant declarations 

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
unsigned long SW1;
void Delay(unsigned long time);  // Delay function

//   Function Prototypes
void PortF_Init(void);

int main(void){
	PortF_Init();
	while(1)
	{
	
	  SW1= GPIO_PORTF_DATA_R&0x10;
	  SW1=SW1^0x10;
	  if(SW1==0x10){
	  GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R^0x08;
		Delay(2); //Delay of few random seconds
	  }
	  else 
	  {
    	GPIO_PORTF_DATA_R|=0x08;
	  } 	
	}
}

void PortF_Init(void) {
	
	// PF4 - SW1 and PF3 - Green LED
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     //  F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R &= ~0x10;        // PF4 input  
	GPIO_PORTF_DIR_R |= 0x08;         //PF3 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // no alternate function
  GPIO_PORTF_PUR_R = 0x10;          // enable pullup resistors on PF4   
  GPIO_PORTF_DEN_R = 0x18;          // enable digital pins PF4 and PF3 
};


void Delay(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 133333;  
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; 
  }
}
