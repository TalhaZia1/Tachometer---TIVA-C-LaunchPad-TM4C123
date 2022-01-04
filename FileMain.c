#include <stdio.h>
#include <math.h>
#include "functions.h"

void SysTick_Handler   (void);
void GPIOPortF_Handler (void);

int main (void)
{
	Timer1A_Init();
	GPIO_Port_Init();
	LCD_Init();
	LCD_Clear();
	SysTickConfig();
	while (1)
	{
		WaitForInterrupt();
		if(delta==1)
		{
			ftoa(catchans, res, 4);
			LCD_GoTo_XY(1,1);
			LCD_Send_String("Speed of Motor");
			LCD_GoTo_XY(1,2);
			LCD_Send_String(res);
			LCD_GoTo_XY(14,2);
			LCD_Send_String("rpm");
			Delay(200000);
		}
	}
}

void SysTick_Handler   (void){
	ST_CTRL_R &= ~countflag;
	beta++;
} 
void GPIOPortF_Handler (void){
	if((GPIO_PORTF_DATA_PF1 & 0x2) == 0 )
	{		
		GPIO_PORTF_ICR_R |= PF1;
		if (alpha==0)
		{
			ST_CTRL_R |= 0x1;
			alpha++;
			delta =0;
		}
		else if (alpha==1)
		{
			ST_CTRL_R &= ~0x1;
			catchans = ST_RELOAD_R - ST_CURRENT_R;
			catchans = catchans*(0.0000000625);
			catchans=catchans+beta;
			catchans=1/catchans;
			catchans=catchans*2*3.1416;
			catchans=catchans*60 ;
			catchans=catchans/2;
			catchans=catchans/3.1416;
			delta=1;
			alpha=0;
			beta=0;
			ST_CURRENT_R = 0x0;
		}
	}
	else if((GPIO_PORTF_DATA_PF4 & 0x10) == 0 )
	{
		GPIO_PORTF_ICR_R |= PF4;
		if(newduty==0)
		{
			TIM_A_MATCH = 15500;
			newduty++;
		}
		else if(newduty==1)
		{
			TIM_A_MATCH = 15000;
			newduty++;
		}
		else if(newduty==2)
		{
			TIM_A_MATCH = 14500;
			newduty++;
		}
		else if(newduty==3)
		{
			TIM_A_MATCH = 14000;
			newduty++;
		}
		else if(newduty==4)
		{
			TIM_A_MATCH = 13500;
			newduty++;
		}
		else if(newduty==5)
		{
			TIM_A_MATCH = 13000;
			newduty=0;
		}
	
		GPTM_CONTROL_R &= ~(TIM_A_ENABLE);
		GPTM_TA_MATCH_R = TIM_A_MATCH;
		GPTM_CONTROL_R |= TIM_A_ENABLE;
	}
}

