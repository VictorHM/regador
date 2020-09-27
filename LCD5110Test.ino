#include <PCD8544.h>
 PCD8544 lcd;
void setup() {
   lcd.begin(84, 48);
}
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME  ");
  lcd.setCursor(0, 1);
  lcd.print("     To");
  lcd.setCursor(0,2);
  lcd.print("ElectronicsHobbyists.com");
  delay(200);
 }
