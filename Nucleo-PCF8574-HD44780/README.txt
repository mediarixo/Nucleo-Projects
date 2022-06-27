Toolchain: uVision 5.2, (C) Keil Software

Pinout:

(function) (mcu) (arduino)          (pcf8574)
I2C1_SCL =  PB8  (D15 @ CN5)      = SCL  
I2C1_SDA =  PB9  (D14 @ CN5)      = SDA
                             5V   = VCC
                             GND  = GND					 
Remarks:
Change the Chip I2C slave address either to 0x27 or 0x3F depending on the IC driver version.