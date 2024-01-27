#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

void Automat(){
	enum LedState{STAND_STILL, STEP_RIGHT, STEP_LEFT}; 
  static enum LedState eLedState = STAND_STILL;
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




int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(20000,&Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
