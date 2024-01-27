#include <LPC21xx.H>
#include "servo.h"
#include "timer_interrupts.h"
#include "led.h"

#define DETECTOR_bm (1<<10)


enum ServoState {CALLIB, IDLE, IN_PROGRESS}; 

struct Servo 
{ 
 enum ServoState eState;  
 unsigned int uiCurrentPosition; 
 unsigned int uiDesiredPosition; 
}; 

struct Servo sServo; 



void DetectorInit(){
 IO0DIR = IO0DIR&(~(DETECTOR_bm));
}

enum DetectorState eReadDetector(){
	if((IO0PIN&DETECTOR_bm)==0){
	  return ACTIVE;
  }
	else{
		return INACTIVE;
	}
}

void Automat(){
  switch(sServo.eState){ 
			
      case IDLE: 
				                  if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
														sServo.eState = IN_PROGRESS;	
													}
                          else{	
                            
														sServo.eState = IDLE;														
													}
                          break; 													
      case IN_PROGRESS:   
				                  if(sServo.uiCurrentPosition == sServo.uiDesiredPosition){
				                     sServo.eState = IDLE;
			                    }
													else{
														if(sServo.uiCurrentPosition>sServo.uiDesiredPosition){
															 LedStepRight();
															 sServo.uiCurrentPosition--;
														}
														else{
															LedStepLeft();
															sServo.uiCurrentPosition++;
														}
														sServo.eState = IN_PROGRESS;
													}
                          break;  
			case CALLIB:        
				                  if(eReadDetector()==ACTIVE){
														sServo.uiCurrentPosition = 0;
														sServo.uiDesiredPosition = 0;
														sServo.eState = IDLE;
													}
													else{
														LedStepLeft();
														sServo.eState = CALLIB;
													}
    }	
}

void ServoInit(unsigned int uiServoFrequency){
	LedInit();
	DetectorInit();
	sServo.eState=CALLIB;	
	Timer0Interrupts_Init((1000000/uiServoFrequency),&Automat);
}

void ServoCallib(void){	
	sServo.eState=CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	while(sServo.eState != IDLE){}
	sServo.uiDesiredPosition = uiPosition;
	sServo.eState = IN_PROGRESS;
}
