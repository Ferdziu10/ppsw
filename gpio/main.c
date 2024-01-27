#include <LPC21xx.H>
#define LED0_bm (1<<16) 
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

#define BUTTON0_bm (1<<4)
#define BUTTON1_bm (1<<6)
#define BUTTON2_bm (1<<5)
#define BUTTON3_bm (1<<7)


unsigned int uiStepIndeks = 0;

enum StepDirection{RIGHT,LEFT};

enum KeyBoardState{RELASED,BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyBoardState eKeyBoardRead()
{if ((IO0PIN&BUTTON0_bm)==0){
	return BUTTON_0;
}
else if ((IO0PIN&BUTTON1_bm)==0){
	return BUTTON_1;
}
else if ((IO0PIN&BUTTON2_bm)==0){
	return BUTTON_2;
}
else if ((IO0PIN&BUTTON3_bm)==0){
	return BUTTON_3;
}
else{
	return RELASED;
}
}
/*
opóznienie w ms
*/

void Delay(unsigned int uiTime){
	unsigned int uiCounter;
	uiTime = uiTime * 100000;
  for(uiCounter = 0; uiCounter < uiTime; uiCounter++){
		continue;
	}

}

/*
ustawia piny podpiete do LED0-LED3 na wyjsciowe oraz zapala LED0
ustawia kierunek tylko pinów odpowiadajacych LED0-LED3.
Kierunek pozostalych pinów powinien zostac niezmieniony.
*/

void LedInit(){
	
	IO1DIR = IO1DIR|(LED0_bm | LED1_bm | LED2_bm | LED3_bm ); 
	IO1SET = LED0_bm;
}

void KeyboardInit(){
	IO0DIR = IO0DIR&(~(BUTTON0_bm|BUTTON1_bm|BUTTON2_bm|BUTTON3_bm));	
}




void LedOn(unsigned char ucLedIndeks){
	IO1CLR =(LED0_bm | LED1_bm | LED2_bm | LED3_bm ); 
	switch(ucLedIndeks){
		case 0 :    IO1SET = LED0_bm;
		            break;
		
		case 1 :    IO1SET = LED1_bm;
		            break;
		
		case 2 :    IO1SET = LED2_bm;
		            break;
		
		case 3 :    IO1SET = LED3_bm;
		            break;
		
		default : break;
 }
}




void LedStep(enum StepDirection eDirection){
	
	static unsigned int uiCurrentDiode;

	if (eDirection == LEFT ){
		uiCurrentDiode++;}
		else{
		uiCurrentDiode--;
	}
	LedOn(uiCurrentDiode%4);
}														



void LedStepLeft(){
	LedStep(LEFT);
}

void LedStepRight(){
	LedStep(RIGHT);
}

int main(){
	
	
  LedInit();
	KeyboardInit();

	
	
  while(1){ 
    switch(eKeyBoardRead()){
			case BUTTON_1:     LedStepRight();
			                   break;
			
			case BUTTON_2:     LedStepLeft();
			                   break;
			
			default:           break;
			
		}	
    Delay(100);		
		}
	}


