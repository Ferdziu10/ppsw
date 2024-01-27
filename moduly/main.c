#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiTime){
	unsigned int uiCounter;
	uiTime = uiTime * 100000;
  for(uiCounter = 0; uiCounter < uiTime; uiCounter++){
		continue;
	}
}


int main(){
	
  LedInit();
	KeyboardInit();

  while(1){ 
    switch(eKeyboardRead()){
			case BUTTON_1:     LedStepRight();
			                   break;
			
			case BUTTON_2:     LedStepLeft();
			                   break;
			
			default:           break;
			
		}	
    Delay(100);		
		}
	}

