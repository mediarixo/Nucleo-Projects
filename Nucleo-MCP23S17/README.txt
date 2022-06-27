Toolchain: uVision 5.2, (C) Keil Software

Pinout:

(function) (mcu) (arduino)          (mcp23s17)
SPI1_SCK =  PA5  (D13 @ CN5)      = SCK  
SPI1_MISO = PA6  (D12 @ CN5)      = MISO = [NC]
SPI1_MOSI = PA7  (D11 @ CN5)      = MOSI 
SPI1_CS  =  PB6  (D10 @ CN5)      = ~CS  

Remarks:
~RST = +5V = Vdd                                  
A2,A1,A0 = Vss
INTA,INTB = [NC]
