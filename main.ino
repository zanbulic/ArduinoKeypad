#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4; 
const byte COLS = 4; 
int curs = 0;
int cur1 = 0;
int cur2 = 0;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', ' ', 'D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {6, 7, 8, 9}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  lcd.begin();
  Serial.begin(9600);

  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    if (customKey != 'C' && customKey != 'D') {
      if (curs == 0) {
        cur1++;
      } else {
        cur2++;
      }
      lcd.print(customKey);
      if (cur1 >= 16 && curs == 0) {
        lcd.setCursor(cur2, 1);
        curs = 1;
      }
    }
  
    if (customKey == 'C') {
      if (curs == 0){
        lcd.setCursor(cur2, 1);
        curs = 1;
      } else {
        lcd.setCursor(cur1, 0);
        curs = 0;
      }
    }
    
    if (customKey == 'D') {
      lcd.clear();
      cur1 = 0;
      cur2 = 0;
      curs = 0;
    }
  }
}
