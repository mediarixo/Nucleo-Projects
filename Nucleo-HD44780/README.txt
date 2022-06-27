Toolchain: uVision 5.1, (C) Keil Software

Pinout 8-bit:

(LCD)  (arduino)  (mcu)    
RS   = D15 ...  -> PB8
RW   = D14 ...  -> PB9
E    = D13 ...  -> PA5 

D0   = D2  ...  -> PA10
D1   = D4  ...  -> PB5 
D2   = D6  ...  -> PB10
D3   = D7  ...  -> PA8 
D4   = D8  ...  -> PA9
D5   = D9  ...  -> PC7
D6   = D10 ...  -> PB6
D7   = D11 ...  -> PA7


Pinout 4-bit:

(LCD)  (arduino)  (mcu)    
RS   = D15 ...  -> PB8
RW   = D14 ...  -> PB9
E    = D13 ...  -> PA5 

D4   = D8  ...  -> PA9
D5   = D9  ...  -> PC7
D6   = D10 ...  -> PB6
D7   = D11 ...  -> PA7


Remarks:

EN = 0 
EN = 1 - used to secure information into the internal register
RW = 0 - used to write to the LCD
RW = 1 - used to read from the LCD
RS = 0 - command register (ie. send command to lcd) 0x01
RS = 1 - data register (ie. send data to lcd) 'A'
