Toolchain: uVision 5.2, (C) Keil Software

Pinout:

(function) (mcu) (arduino)          (sim800l)
USART1_TX   PA9  (D8 @ CN5)       =  RX
USART1_RX   PA10 (D2 @ CN9)       =  TX

Remarks:                           
Vdd = 3.7 V Li-Po Battery
GND wired both to sim800l module and board.									


Software used as serial terminal: PuTTY release 0.67

Remarks:
Configuration must match both Nucleo Virtual COM port and SIM module.

Serial line:  COM4 (may differ)
Speed (baud): 9600
Data bits: 8
Stop bits: 1
Parity: None
Flow control: None