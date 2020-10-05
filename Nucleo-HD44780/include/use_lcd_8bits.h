#define NONE 0
#define OR   1

void delay_micro(int n);
void delay_milli(int n);
void LCD_init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data(unsigned char data);

static void PIN_init(GPIO_TypeDef* GPIOx, uint16_t pin_no, uint16_t mode);
static void PIN_high(GPIO_TypeDef* GPIOx, uint16_t pin_no);
static void PIN_low(GPIO_TypeDef* GPIOx, uint16_t pin_no);
static void LCD_set_control(unsigned char data, bool par);
static void LCD_set_data(unsigned char newcommand);

void LCD_init(void)
{
	RCC->AHB1ENR |=  (1 << 0);	
	RCC->AHB1ENR |=  (1 << 1);  
	RCC->AHB1ENR |=  (1 << 2);  
	
	PIN_init(GPIOA, 5, 0x01); 
	PIN_init(GPIOA, 7, 0x01);
	PIN_init(GPIOA, 8, 0x01);
	PIN_init(GPIOA, 9, 0x01);
	PIN_init(GPIOA, 10, 0x01);
	PIN_init(GPIOB, 5, 0x01);
	PIN_init(GPIOB, 6, 0x01);
	PIN_init(GPIOB, 8, 0x01);
	PIN_init(GPIOB, 9, 0x01);
	PIN_init(GPIOB, 10, 0x01);
	PIN_init(GPIOC, 7, 0x01);
	
	LCD_Cmd(0x38);		
	LCD_Cmd(0x06);		
	LCD_Cmd(0x0F);		
	LCD_Cmd(0x01);		
}

void LCD_Data(unsigned char data)
{	
	LCD_set_control(0x20, NONE); 
	LCD_set_data(data);
	LCD_set_control(0x80, OR);   
	delay_micro(50);              
	LCD_set_control(0x00, NONE); 
	delay_micro(0);
}

void LCD_Cmd(unsigned char command)
{
	LCD_set_control(0x00, NONE); 
	LCD_set_data(command);
	LCD_set_control(0x80, NONE); 
	delay_micro(20);							 
	LCD_set_control(0x00, NONE); 
	if (command < 4)
		delay_milli(2);
	else
		delay_micro(37);
}

void delay_micro(int n)
{
	int i, j;
	for (i=0; i<n; i++)
	 for (j=0; j<3; j++)
	  {}
}

void delay_milli(int n)
{
	int i, j;
	for (i=0; i<n; i++)
	 for (j=0; j<3180; j++)
	  {}
}

static void PIN_init(GPIO_TypeDef* GPIOx, uint16_t pin_no, uint16_t mode) 
{
	GPIOx->MODER |= ( mode << (2 * pin_no) );	
	GPIOx->OTYPER |= ( 0x00 << (pin_no) );   
	GPIOx->OSPEEDR |= ( 0x03 << (2 * pin_no) ); 
	GPIOx->PUPDR |= ( 0x00 << (2 * pin_no) ); 
}

static void PIN_high(GPIO_TypeDef* GPIOx, uint16_t pin_no) 
{
	GPIOx->ODR |= ( 1 << pin_no );
}

static void PIN_low(GPIO_TypeDef* GPIOx, uint16_t pin_no) 
{
	GPIOx->ODR &= ~( 1 << pin_no );
}

static void LCD_set_control(unsigned char data, bool par)
{
	static unsigned char newdata;
	if (par == 1)	//OR
		newdata |= data;
	else
		newdata = data;

	bool EN = (newdata >> 7) & 0x01;		
	bool RW = (newdata >> 6) & 0x01;
	bool RS = (newdata >> 5) & 0x01;
		
	if (EN == 0) 
		PIN_low(GPIOA, 5); 
	else
		PIN_high(GPIOA, 5);       
	
  if (RW == 0)
		PIN_low(GPIOB, 9);       
	else
		PIN_high(GPIOB, 9);      
	
	if (RS == 0) 
		PIN_low(GPIOB, 8);       
	else
		PIN_high(GPIOB, 8);       
}

static void LCD_set_data(unsigned char command)
{		
	bool D7 = (command >> 7) & 0x01;
	bool D6 = (command >> 6) & 0x01;
	bool D5 = (command >> 5) & 0x01;
	bool D4 = (command >> 4) & 0x01;
	bool D3 = (command >> 3) & 0x01;
	bool D2 = (command >> 2) & 0x01;
	bool D1 = (command >> 1) & 0x01;
	bool D0 = (command >> 0) & 0x01;
	
	if (D7 == 0)
		PIN_low(GPIOA, 7);
	else
		PIN_high(GPIOA, 7);
	
	if (D6 == 0)
		PIN_low(GPIOB, 6);
	else
		PIN_high(GPIOB, 6);

	if (D5 == 0)
		PIN_low(GPIOC, 7);
	else
		PIN_high(GPIOC, 7);

	if (D4 == 0)
		PIN_low(GPIOA, 9);
	else
		PIN_high(GPIOA, 9);

	if (D3 == 0)
		PIN_low(GPIOA, 8);
	else
		PIN_high(GPIOA, 8);

	if (D2 == 0)
		PIN_low(GPIOB, 10);
	else
		PIN_high(GPIOB, 10);

	if (D1 == 0)
		PIN_low(GPIOB, 5);
	else
		PIN_high(GPIOB, 5);

	if (D0 == 0)
		PIN_low(GPIOA, 10);
	else
		PIN_high(GPIOA, 10);
}	
