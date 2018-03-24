//##########################################################################
//
// lcall3 Controller is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// lcall3 Controller is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lcall3 Controller. If not, see <http://www.gnu.org/licenses/>.
//
//##########################################################################

#ifndef OLED_h
#define OLED_h

#include "Arduino.h"

#define VERTICAL_MODE                       01
#define HORIZONTAL_MODE                     02

#define OLED_Address               0x3c
#define OLED_Command_Mode          0x80
#define OLED_Data_Mode             0x40

#define OLED_Display_Off_Cmd       0xAE
#define OLED_Display_On_Cmd        0xAF

#define OLED_Normal_Display_Cmd    0xA4
#define OLED_Inverse_Display_Cmd   0xA7
#define OLED_Activate_Scroll_Cmd   0x2F
#define OLED_Deactivate_Scroll_Cmd 0x2E
#define OLED_Set_ContrastLevel_Cmd 0x81

#define Scroll_Left             0x00
#define Scroll_Right            0x01

#define Scroll_2Frames          0x7
#define Scroll_3Frames          0x4
#define Scroll_4Frames          0x5
#define Scroll_5Frames          0x0
#define Scroll_25Frames         0x6
#define Scroll_64Frames         0x1
#define Scroll_128Frames        0x2
#define Scroll_256Frames        0x3


class OLED {

public:

char addressingMode;

void init();

void setNormalDisplay();
void setInverseDisplay();

void sendCommand(unsigned char command);
void sendData(unsigned char Data);
void setGrayLevel(unsigned char grayLevel);

void setVerticalMode();
void setHorizontalMode();

void setTextXY(unsigned char Row, unsigned char Column);
void clearDisplay();
void setContrastLevel(unsigned char ContrastLevel);
void putChar(unsigned char c);
void putString(const char *String);
unsigned char putNumber(long n);
unsigned char putFloat(float floatNumber,unsigned char decimal);
unsigned char putFloat(float floatNumber);

void drawBitmap(const unsigned char *bitmaparray,int bytes);

void setHorizontalScrollProperties(bool direction,unsigned char startRow, unsigned char endRow,unsigned char startColumn, unsigned char endColumn, unsigned char scrollSpeed);
void activateScroll();
void deactivateScroll();

private:

unsigned char grayH;
unsigned char grayL;

};

// Preinstantiate object
extern OLED oled;

#endif


