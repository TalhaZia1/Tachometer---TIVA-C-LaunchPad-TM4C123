#define RCGC_TIMER_R         (*(volatile unsigned long *) 0x400FE604)
#define RCGC2_GPIO_R         (*(volatile unsigned long *) 0x400FE608)

#define CLOCK_GPIOF           0x00000020
#define SYS_CLOCK_FREQUENCY   16000000

#define TM_BASE               0x40031000

#define GPTM_CONFIG_R        (*(volatile unsigned long *) (TM_BASE + 0x000))
#define GPTM_TA_MODE_R       (*(volatile unsigned long *) (TM_BASE + 0x004))
#define GPTM_CONTROL_R       (*(volatile unsigned long *) (TM_BASE + 0x00C))
#define GPTM_INT_MASK_R      (*(volatile unsigned long *) (TM_BASE + 0x018))
#define GPTM_INT_CLEAR_R     (*(volatile unsigned long *) (TM_BASE + 0x024))
#define GPTM_TA_IL_R         (*(volatile unsigned long *) (TM_BASE + 0x028))
#define GPTM_TA_MATCH_R      (*(volatile unsigned long *) (TM_BASE + 0x030))

#define TIM_16_BIT_CONFIG     0x00000004
#define TIM_PERIODIC_MODE     0x00000002
#define TIM_A_ENABLE          0x00000001

#define TIM_PWM_MODE          0x0000000A
#define TIM_CAPTURE_MODE      0x00000004

#define TIM_A_INTERVAL        16000

#define SYSCTL_RCGCGPIO_R    (*((volatile unsigned long *) 0x400FE608))
#define NVIC_EN0_R           (*((volatile unsigned long *) 0xE000E100))
//for PortB 
#define GPIOPORTB_DATA       (*((volatile unsigned long *) 0x400053FC))
#define GPIOPORTB_DEN        (*((volatile unsigned long *) 0x4000551C))
#define GPIOPORTB_DIR        (*((volatile unsigned long *) 0x40005400))
#define GPIOPORTB_AFSEL      (*((volatile unsigned long *) 0x40005420))
//for PortE
#define GPIOPORTE_DATA       (*((volatile unsigned long *) 0x400240E0))
#define GPIOPORTE_DEN        (*((volatile unsigned long *) 0x4002451C))
#define GPIOPORTE_DIR        (*((volatile unsigned long *) 0x40024400))
#define GPIOPORTE_AFSEL      (*((volatile unsigned long *) 0x40024420))
//LCD module control pins 
#define LCD_E_PIN             0x08 
#define LCD_RW_PIN            0x10
#define LCD_RS_PIN            0x20
#define LCD_DATA_BUS          GPIOPORTB_DATA
#define LCD_CONTROL_BUS       GPIOPORTE_DATA
#define SYSCTL_RCGCGPIO_R 	 (*((volatile unsigned long *) 0x400FE608))
#define GPIO_PORTF_DATA_PF3  (*((volatile unsigned long *) 0x40025020))
#define GPIO_PORTF_DATA_PF2  (*((volatile unsigned long *) 0x40025010))
#define GPIO_PORTF_DATA_PF1  (*((volatile unsigned long *) 0x40025008))
#define GPIO_PORTF_DATA_PF4  (*((volatile unsigned long *) 0x40025040))	
#define GPIO_PORTF_AFSEL_R   (*((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_PCTL_R    (*((volatile unsigned long *) 0x4002552C))
#define GPIO_PORTF_DEN_R     (*((volatile unsigned long *) 0x4002551C))
// Definitions for GPIO port F	
#define GPIO_PORTF_DIR_R  	 (*((volatile unsigned long *) 0x40025400))
#define GPIOPORTF_DATA_PF1 	 (*((volatile unsigned long *) 0x40025008))
//for interrupt
#define GPIOPORTF_DATA_PF4   (*((volatile unsigned long *) 0x40025040))
#define GPIOPORTF_PUL        (*((volatile unsigned long *) 0x40025510))
#define PF4                   0x10
//interrupt on Port F 
#define GPIO_PORTF_IS_R      (*((volatile unsigned long *) 0x40025404))
#define GPIO_PORTF_IBE_R     (*((volatile unsigned long *) 0x40025408))
#define GPIO_PORTF_IEV_R     (*((volatile unsigned long *) 0x4002540C))
#define GPIO_PORTF_ICR_R     (*((volatile unsigned long *) 0x4002541C))
#define GPIO_PORTF_IM_R      (*((volatile unsigned long *) 0x40025410))
//Port F enabling pins 
#define CLK_ENABLE            0x20
#define PF1                   0x2
//Interrupt enabling
#define enableint             0x40000000
#define countflag             0x00010000
// Definitions for SysTick Timer
#define ST_CTRL_R						 (*((volatile unsigned long *) 0xE000E010))
#define ST_RELOAD_R					 (*((volatile unsigned long *) 0xE000E014))
#define ST_CURRENT_R				 (*((volatile unsigned long *) 0xE000E018))

