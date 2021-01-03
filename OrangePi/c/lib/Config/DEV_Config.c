/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team (modified by Masatrad.com)
* | Function    :   Hardware underlying interface (compatibility with Orange Pi Lite - Armbian)
* | Info        :
*----------------
* |	This version:   V3.0.OrangePiLite
* | Date        :   2021-01-03
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
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
#include "DEV_Config.h"
#include <fcntl.h>

/**
 * GPIO
**/
int EPD_RST_PIN;
int EPD_DC_PIN;
int EPD_CS_PIN;
int EPD_BUSY_PIN;

/**
 * GPIO read and write
**/
void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
	digitalWrite(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
	UBYTE Read_value = 0;
	Read_value = digitalRead(Pin);
	return Read_value;
}

/**
 * SPI
**/
void DEV_SPI_WriteByte(uint8_t Value)
{
	wiringPiSPIDataRW(0,&Value,1);

}

void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len)
{
	wiringPiSPIDataRW(0, pData, Len);
}

/**
 * GPIO Mode
**/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
	if(Mode == 0 || Mode == INPUT) {
		pinMode(Pin, INPUT);
		pullUpDnControl(Pin, PUD_UP);
	} else {
		pinMode(Pin, OUTPUT);
		// Debug (" %d OUT \r\n",Pin);
	}
}

/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{
	delay(xms);
}

static int DEV_Equipment_Testing(void)
{
	int i;
	int fd;
	char value_str[20];
	fd = open("/etc/issue", O_RDONLY);
    printf("Current environment: ");
	while(1) {
		if (fd < 0) {
			Debug( "Read failed Pin\n");
			return -1;
		}
		for(i=0;; i++) {
			if (read(fd, &value_str[i], 1) < 0) {
				Debug( "failed to read value!\n");
				return -1;
			}
			if(value_str[i] ==32) {
				printf("\r\n");
				break;
			}
			printf("%c",value_str[i]);
		}
		break;
	}

	if(i<5) {
		printf("Unrecognizable\r\n");
	} else {
		char RPI_System[10]   = {"Armbian"};
		for(i=0; i<6; i++) {
			if(RPI_System[i]!= value_str[i]) {
				printf("This installation is only for Armbian, your system is $c.\r\n",value_str[i]);
				return -1;
			}
		}
	}
	return 0;
}



void DEV_GPIO_Init(void)
{
	EPD_RST_PIN     = 17;
	EPD_DC_PIN      = 25;
	EPD_CS_PIN      = 8;
	EPD_BUSY_PIN    = 24;

	DEV_GPIO_Mode(EPD_RST_PIN, 1);
	DEV_GPIO_Mode(EPD_DC_PIN, 1);
	DEV_GPIO_Mode(EPD_CS_PIN, 1);
	DEV_GPIO_Mode(EPD_BUSY_PIN, 0);

	DEV_Digital_Write(EPD_CS_PIN, 1);
}
/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(void)
{
    printf("/***********************************/ \r\n");
	if(DEV_Equipment_Testing() < 0) {
		return 1;
	}

	//if(wiringPiSetup() < 0)//use wiringpi Pin number table
	if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
		printf("set wiringPi lib failed	!!! \r\n");
		return 1;
	} else {
		printf("set wiringPi lib success !!! \r\n");
	}

	// GPIO Config
	DEV_GPIO_Init();
	wiringPiSPISetup(0,10000000);
	// wiringPiSPISetupMode(0, 32000000, 0);

    printf("/***********************************/ \r\n");
	return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_Module_Exit(void)
{
	DEV_Digital_Write(EPD_CS_PIN, 0);
	DEV_Digital_Write(EPD_DC_PIN, 0);
	DEV_Digital_Write(EPD_RST_PIN, 0);
}

