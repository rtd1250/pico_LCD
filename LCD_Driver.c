/*****************************************************************************
* | File      	:	LCD_Driver.c
* | Author      :   Waveshare team
* | Function    :   LCD driver
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2018-12-18
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "LCD_Driver.h"

static void LCD_Reset(void) {
    sleep_ms(200);
    gpio_put(DEV_RST_PIN, 0);
    sleep_ms(200);
    gpio_put(DEV_RST_PIN, 1);
    sleep_ms(200);
}

static void rpi_write(uint8_t data) {
    spi_write_blocking(spi_default, &data, 1);
}

static void LCD_Write_Command(uint8_t data) {
    gpio_put(DEV_CS_PIN, 0);
    gpio_put(DEV_DC_PIN, 0);
    spi_write_blocking(spi_default, &data, 1);
}

static void LCD_WriteData_Byte(uint8_t data) {
    gpio_put(DEV_CS_PIN, 0);
    gpio_put(DEV_DC_PIN, 1);
    spi_write_blocking(spi_default, &data, 1);
    gpio_put(DEV_CS_PIN, 1);
}

void LCD_WriteData_Word(uint8_t data) {
    gpio_put(DEV_CS_PIN, 0);
    gpio_put(DEV_DC_PIN, 1);
    //write funny byteshift...
    spi_write_blocking(spi_default, &data, 1);
    gpio_put(DEV_CS_PIN, 1);
}

void LCD_Init(void) {
    LCD_Reset();

    LCD_Write_Command(0x11); //Sleep out

    LCD_Write_Command(0xCF);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0xC1);
    LCD_WriteData_Byte(0X30);
    LCD_Write_Command(0xED);
    LCD_WriteData_Byte(0x64);
    LCD_WriteData_Byte(0x03);
    LCD_WriteData_Byte(0X12);
    LCD_WriteData_Byte(0X81);
    LCD_Write_Command(0xE8);
    LCD_WriteData_Byte(0x85);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x79);
    LCD_Write_Command(0xCB);
    LCD_WriteData_Byte(0x39);
    LCD_WriteData_Byte(0x2C);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x34);
    LCD_WriteData_Byte(0x02);
    LCD_Write_Command(0xF7);
    LCD_WriteData_Byte(0x20);
    LCD_Write_Command(0xEA);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x00);
    LCD_Write_Command(0xC0); //Power control
    LCD_WriteData_Byte(0x1D); //VRH[5:0]
    LCD_Write_Command(0xC1); //Power control
    LCD_WriteData_Byte(0x12); //SAP[2:0];BT[3:0]
    LCD_Write_Command(0xC5); //VCM control
    LCD_WriteData_Byte(0x33);
    LCD_WriteData_Byte(0x3F);
    LCD_Write_Command(0xC7); //VCM control
    LCD_WriteData_Byte(0x92);
    LCD_Write_Command(0x3A); // Memory Access Control
    LCD_WriteData_Byte(0x55);
    LCD_Write_Command(0x36); // Memory Access Control
    LCD_WriteData_Byte(0x08);
    LCD_Write_Command(0xB1);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x12);
    LCD_Write_Command(0xB6); // Display Function Control
    LCD_WriteData_Byte(0x0A);
    LCD_WriteData_Byte(0xA2);

    LCD_Write_Command(0x44);
    LCD_WriteData_Byte(0x02);

    LCD_Write_Command(0xF2); // 3Gamma Function Disable
    LCD_WriteData_Byte(0x00);
    LCD_Write_Command(0x26); //Gamma curve selected
    LCD_WriteData_Byte(0x01);
    LCD_Write_Command(0xE0); //Set Gamma
    LCD_WriteData_Byte(0x0F);
    LCD_WriteData_Byte(0x22);
    LCD_WriteData_Byte(0x1C);
    LCD_WriteData_Byte(0x1B);
    LCD_WriteData_Byte(0x08);
    LCD_WriteData_Byte(0x0F);
    LCD_WriteData_Byte(0x48);
    LCD_WriteData_Byte(0xB8);
    LCD_WriteData_Byte(0x34);
    LCD_WriteData_Byte(0x05);
    LCD_WriteData_Byte(0x0C);
    LCD_WriteData_Byte(0x09);
    LCD_WriteData_Byte(0x0F);
    LCD_WriteData_Byte(0x07);
    LCD_WriteData_Byte(0x00);
    LCD_Write_Command(0XE1); //Set Gamma
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x23);
    LCD_WriteData_Byte(0x24);
    LCD_WriteData_Byte(0x07);
    LCD_WriteData_Byte(0x10);
    LCD_WriteData_Byte(0x07);
    LCD_WriteData_Byte(0x38);
    LCD_WriteData_Byte(0x47);
    LCD_WriteData_Byte(0x4B);
    LCD_WriteData_Byte(0x0A);
    LCD_WriteData_Byte(0x13);
    LCD_WriteData_Byte(0x06);
    LCD_WriteData_Byte(0x30);
    LCD_WriteData_Byte(0x38);
    LCD_WriteData_Byte(0x0F);
    LCD_Write_Command(0x29); //Display on
}

void LCD_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{ 
	LCD_Write_Command(0x2a);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(Xstart & 0xff);
	LCD_WriteData_Byte((Xend - 1) >> 8);
	LCD_WriteData_Byte((Xend - 1) & 0xff);

	LCD_Write_Command(0x2b);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(Ystart & 0xff);
	LCD_WriteData_Byte((Yend - 1) >> 8);
	LCD_WriteData_Byte((Yend - 1) & 0xff);

	LCD_Write_Command(0x2C);
}

void LCD_Clear(uint16_t Color)
{
	unsigned int i,j;
	LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
	gpio_put(DEV_DC_PIN, 1);
	for(i = 0; i < LCD_WIDTH; i++){
		for(j = 0; j < LCD_HEIGHT; j++){
			rpi_write((Color>>8)&0xff);
			rpi_write(Color);
		}
	}
}
