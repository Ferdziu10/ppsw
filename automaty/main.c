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
	
	enum LedState{STAND_STILL, STEP_RIGHT, STEP_LEFT}; 
  enum LedState eLedState = STAND_STILL;	

	LedInit();
	KeyboardInit();
	
  while(1){ 
		Delay(10);
    switch(eLedState){ 
      case STEP_LEFT: 
				                  if(eKeyBoardRead() == BUTTON_1){
														eLedState = STAND_STILL;	
													}
                          else{	
                            LedStepLeft();
														eLedState = STEP_LEFT;														
													}
                          break;
      case STEP_RIGHT: 
				                  if(eKeyBoardRead() == BUTTON_1){
														eLedState = STAND_STILL;	
													}
                          else{	
                            LedStepRight();
														eLedState = STEP_RIGHT;														
													}
                          break; 													
      case STAND_STILL:   
				                  if(eKeyBoardRead() == BUTTON_2){
				                     eLedState = STEP_RIGHT;
			                    }
													else if(eKeyBoardRead() == BUTTON_0){
				                     eLedState = STEP_LEFT;
			                    }
													else{
														eLedState = STAND_STILL;
													}
                          break;  
    }
  } 
}
