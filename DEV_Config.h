/*****************************************************************************
* | File        :   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2018-11-22
* | Info        :

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
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

/**
 * GPIO config
**/

/*
    Vcc - 3.3V
    GND - ground
    DIN - SPI0 MOSI/TX - PICO_DEFAULT_SPI_TX_PIN (19)
    CLK - SPI0 SCLK - PICO_DEFAULT_SPI_SCK_PIN (18)
    CS  - SPI0 CE0 - PICO_DEFAULT_SPI_CSN_PIN (17)
    DC  - gpio - 20
    RST - gpio - 21
    BL  - SPI1 CE0 - 13
*/
#define DEV_CS_PIN  PICO_DEFAULT_SPI_CSN_PIN
#define DEV_DC_PIN  20
#define DEV_RST_PIN 21
#define DEV_BL_PIN  13

#endif
