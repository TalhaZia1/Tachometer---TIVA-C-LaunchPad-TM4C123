//LCD module control pins 
#define LCD_E_PIN           0x08 
#define LCD_RW_PIN          0x10
#define LCD_RS_PIN          0x20
#define LCD_DATA_BUS        GPIOPORTB_DATA
#define LCD_CONTROL_BUS     GPIOPORTE_DATA



void LCD_Init(void);
void LCD_Clear(void);
void LCD_Send_Command(unsigned char command);
void LCD_Send_Data(unsigned char data);
void LCD_GoTo_XY(unsigned char x, unsigned char y);
void LCD_Send_String(char *ptr);

void LCD_Send_Command(unsigned char command)
{
	LCD_DATA_BUS = command;
	LCD_CONTROL_BUS = 0;
	Delay(1);
	LCD_CONTROL_BUS |= LCD_E_PIN;
	Delay(1);
	LCD_CONTROL_BUS &= ~(LCD_E_PIN);
	Delay(4);
}
void LCD_Send_Data(unsigned char data)
{
	LCD_DATA_BUS = data;
	LCD_CONTROL_BUS = LCD_RS_PIN;
	Delay(1);
	LCD_CONTROL_BUS |= LCD_E_PIN;
	Delay(1);
	LCD_CONTROL_BUS &= ~(LCD_E_PIN);
	Delay(4);
}
void LCD_Init(void)
{
	LCD_CONTROL_BUS = 0;
	Delay(1500);
	LCD_Send_Command(0x38);
	LCD_Send_Command(0x10);
	LCD_Send_Command(0x0E);
	LCD_Send_Command(0x06);
	LCD_Send_Command(0x0C);
}
void LCD_Clear(void)
{
	LCD_Send_Command(0x01);
	Delay(170);
	LCD_Send_Command(0x02);
	Delay(170);
}
void LCD_Send_String(char *ptr)
{
	while(*ptr)
	{
		LCD_Send_Data(*ptr);
		ptr++;
	}
}
void LCD_GoTo_XY(unsigned char x, unsigned char y)
{
	unsigned char row_start_address[]= {0x80, 0xC0};
	LCD_Send_Command(row_start_address[y-1] + x - 1);
	Delay(170);
}
