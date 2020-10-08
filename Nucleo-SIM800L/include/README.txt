Toolchain: uVision 5.2, (C) Keil Software

Pinout:

(function) (mcu) (arduino)          (sim800l)
USART1_TX   PA9  (D8 @ CN5)       =  RX
USART1_RX   PA10 (D2 @ CN9)       =  TX

Remarks:                            
Vdd = 3.7 V Li-Po Battery
GND wired both to sim800l module and board.		
Virtual COM port (USART2 module) is configured with baudrate at 115200 bauds and 1 start bit, 8 data bits and 1 stop bit.
