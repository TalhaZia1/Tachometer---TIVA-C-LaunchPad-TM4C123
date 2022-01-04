#include "header.h"
//Variables Declaration 
double catchans=0,beta=0,alpha=0,delta=0,newduty=0;
char res[20];
int TIM_A_MATCH=8000;
//functions
void SysTickConfig(void);
void GPIO_Port_Init(void);
void Delay (volatile unsigned int delay);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_Send_Command(unsigned char command);
void LCD_Send_Data(unsigned char data);
void LCD_GoTo_XY(unsigned char x, unsigned char y);
void LCD_Send_String(char *ptr);
void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
void Timer1A_Init(void);
//function for interrupt 
void DisableInterrupts (void);
void EnableInterrupts  (void);
void WaitForInterrupt  (void);

void Timer1A_Init(void){

 RCGC2_GPIO_R |= CLOCK_GPIOF;
 RCGC_TIMER_R |= 0x02;
 
 GPIO_PORTF_AFSEL_R |= 0x00000004;
 GPIO_PORTF_PCTL_R |=  0x00000700;
 GPIO_PORTF_DEN_R |=   0x00000004;
	
 GPTM_CONTROL_R &= ~(TIM_A_ENABLE);
 GPTM_CONFIG_R |= TIM_16_BIT_CONFIG;
	
 GPTM_TA_MODE_R |= TIM_PWM_MODE;
 GPTM_TA_MODE_R &= ~(TIM_CAPTURE_MODE);
 GPTM_TA_IL_R = TIM_A_INTERVAL;
 GPTM_TA_MATCH_R = TIM_A_MATCH;
	GPTM_CONTROL_R |= TIM_A_ENABLE;
}

void reverse(char *str, int len){
	 // Converts a given integer x to string str[].  d is the number
	 // of digits required in output. If d is more than the number
	 // of digits in x, then 0s are added at the beginning.
	 // reverses a string 'str' of length 'len'  
		int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
int intToStr(int x, char str[], int d){
    // Converts a floating point number to string.
		int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}
 

void ftoa(float n, char *res, int afterpoint){
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

void SysTickConfig(void){
	
	ST_CTRL_R |= 0x6;
	ST_RELOAD_R = 16000000;
	ST_CURRENT_R = 0x0;
}
 
void GPIO_Port_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x12;
	//for PortB
	GPIOPORTB_DIR |= 0xFF;
	GPIOPORTB_DEN |= 0xFF;
	GPIOPORTB_AFSEL &= ~0xFF;
	//for PortE
	GPIOPORTE_DIR |= 0x38;
	GPIOPORTE_DEN |= 0x38;
	GPIOPORTE_AFSEL &= ~0x38;
	//for PortF
	SYSCTL_RCGCGPIO_R |= CLK_ENABLE;
	GPIO_PORTF_DEN_R |= PF1+PF4;
	GPIOPORTF_PUL |= PF4;
	GPIO_PORTF_DIR_R &= ~(PF1+PF4);
	//Configuration of Interrupt at PortF 
	DisableInterrupts();
	GPIO_PORTF_IS_R &= ~(PF1+PF4);
	GPIO_PORTF_IBE_R &= ~(PF1+PF4);
	GPIO_PORTF_IEV_R &= ~(PF1+PF4);
	GPIO_PORTF_ICR_R |= (PF1+PF4);
	GPIO_PORTF_IM_R |= (PF1+PF4);
	NVIC_EN0_R |= enableint;
	EnableInterrupts();
	
}
void LCD_Send_Command(unsigned char command){
	LCD_DATA_BUS = command;
	LCD_CONTROL_BUS = 0;
	Delay(1);
	LCD_CONTROL_BUS |= LCD_E_PIN;
	Delay(1);
	LCD_CONTROL_BUS &= ~(LCD_E_PIN);
	Delay(4);
}
void LCD_Send_Data(unsigned char data){
	LCD_DATA_BUS = data;
	LCD_CONTROL_BUS = LCD_RS_PIN;
	Delay(1);
	LCD_CONTROL_BUS |= LCD_E_PIN;
	Delay(1);
	LCD_CONTROL_BUS &= ~(LCD_E_PIN);
	Delay(4);
}
void LCD_Init(void){
	LCD_CONTROL_BUS = 0;
	Delay(1500);
	LCD_Send_Command(0x38);
	LCD_Send_Command(0x10);
	LCD_Send_Command(0x0E);
	LCD_Send_Command(0x06);
	LCD_Send_Command(0x0C);
}
void LCD_Clear(void){
	LCD_Send_Command(0x01);
	Delay(170);
	LCD_Send_Command(0x02);
	Delay(170);
}
void LCD_Send_String(char *ptr){
	while(*ptr)
	{
		LCD_Send_Data(*ptr);
		ptr++;
	}
}
void LCD_GoTo_XY(unsigned char x, unsigned char y){
	unsigned char row_start_address[]= {0x80, 0xC0};
	LCD_Send_Command(row_start_address[y-1] + x - 1);
	Delay(170);
}

void Delay (volatile unsigned int delay){
	volatile unsigned int i, j;
	for(i=0;i<delay;i++)
	{
		for(j=0;j<12;j++);
	}
}
