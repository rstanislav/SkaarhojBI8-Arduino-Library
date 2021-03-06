/*****************
 * This example will first run the LED test sequence on SkaarhojBI8 board with address 0 on the I2C bus 
 * You should see all color combinations of the buttons shown
 * Then, in the run loop it will look for button presses and a) cycle the color of the button pressed 
 * and b) print the button number to Serial-out
 * 
 * - kasper
 */

// All related to library "SkaarhojBI8":
#include "Wire.h"
#include "MCP23017.h"
#include "PCA9685.h"
#include "SkaarhojBI8.h"

// Setting up a board:
SkaarhojBI8 board;


void setup() { 
  Serial.begin(9600); // set up serial
  Serial.println("Serial Started");
  
  // Always initialize Wire before setting up the SkaarhojBI8 class!
  Wire.begin(); 
  
  // Set up the board:
  board.begin(0,false);  // Address 0, dip-switch on board is OFF for both 1 and 2
  board.testSequence();  // Runs LED test sequence
}

uint8_t buttonColorTracking[] = {0,0,0,0,0,0,0,0};

void loop() {
  for(int i=1;i<=8;i++)  {
    if (board.buttonDown(i))  {
      Serial.print("Button #");
      Serial.print(i);
      Serial.println(" was pressed down");

      board.setButtonColor(i, nextButtonColor(i));
    }  
    if (board.buttonUp(i))  {
      Serial.print("Button #");
      Serial.print(i);
      Serial.println(" was released");
    }  
  }  
}


uint8_t nextButtonColor(int i) {
  buttonColorTracking[i-1]++;
  if (buttonColorTracking[i-1]>5)  {
    buttonColorTracking[i-1]=0;
  }
  return buttonColorTracking[i-1];
}
