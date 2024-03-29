#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE_bm (1<<0)
#define COUNTER_RESET_bm (1<<1)
#define RESET_ON_MR0_bm (1<<1)
#define INTERRUPT_ON_MR0_bm (1<<0)
#define INTERRUPT_FLAG_MR0_bm (1<<0)
		
void InitTimer0(void){
	T0TCR = (COUNTER_ENABLE_bm | T0TCR );
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR = (T0TCR|COUNTER_RESET_bm);
	T0TCR = (T0TCR&(~COUNTER_RESET_bm));
	while((uiTime*15)>=T0TC){}
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MR0 = (15*iDelayTime);
	T0MCR = (INTERRUPT_ON_MR0_bm | RESET_ON_MR0_bm);
	T0TCR = (T0TCR|COUNTER_RESET_bm);
	T0TCR = (T0TCR&(~COUNTER_RESET_bm));
	T0TCR = (COUNTER_ENABLE_bm | T0TCR );
}
void WaitOnTimer0Match0(){
	while((T0IR&INTERRUPT_FLAG_MR0_bm) == 0){}
	T0IR = INTERRUPT_FLAG_MR0_bm;
}
