#include <PCD8544.h>

PCD8544 lcd;

//Temporary global variables. TODO create class
int x_, y_ = 0;

void LCDsetup(int x0, int y0) {
   lcd.begin(x0, y0);
}

// Set the position of the cursor
void LCDpos(int x, int y){
  assert(x);
  assert(y);
  lcd.setCursor(x, y);
}

void LCDclear() {
  lcd.clear();
}

void LCDwrite(char* message) {
  lcd.print(message);
  lcd.setCursor(x_, y_ + 1);
}

void LCDMeasures(int temp, int humidity) {
  //TODO implement nice text with data
  LCDpos(0, 0);
  //TODO write messages
  lcd.print("Temp: %d \n", temp);
  lcd.setCursor(x_, y_ + 1);
  lcd.print("Humidity: %d \n", humidity);
}

//TODO try Draw a chart element at the current cursor position...
// function void drawColumn(uint8_t lines, uint8_t value);
// to see if it can draw a table for the data.


// TODO setStop() to disable the screen if a button is pulsed and viceversa.
