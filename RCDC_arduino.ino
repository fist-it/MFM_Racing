#include <Wire.h>

#include <LiquidCrystal_I2C.h>

//WYSWIETLACZ oparty na PCF8574


const int BUTTON_PIN = 2;
const int LED_PIN_1 = 3;
const int LED_PIN_2 = 5;
const int LED_PIN_3 = 7;
const int countDelay = 1000;
int newbutton = 0;
int oldbutton = 0;// Poprzedni stan przycisku

int clickCount = 0;
int clickDebounceDelay = 200;
int previousClickTime = 0;

int counter = 0;
int extra_time = 0;

int thirdLedCounter = 0;
int thirdLedState = 0;
int possibleChangeOfThirdLed = 1;

unsigned long previousTime = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adres I2C może się różnić (np. 0x3F)

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  
  lcd.init();       // Inicjalizacja LCD
  lcd.backlight();  // Włącz podświetlenie
  lcd.setCursor(0, 0);
  lcd.print("1: L");
  lcd.setCursor(0, 1);
  lcd.print("2: L");
  lcd.setCursor(5, 0);
  lcd.print("3: L");

}

void countWithDelay() {
  if (millis() - previousTime >= countDelay) {
    previousTime = millis();
    counter++;
    thirdLedCounter++;
    Serial.println(counter);
    Serial.println(thirdLedCounter);
  }
}


void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  countWithDelay();
  
  if (buttonState==1) { 
      if (millis() - previousClickTime >= clickDebounceDelay) { // button click
                                                                // debounce
        clickCount++;
        previousClickTime = millis();
      }

      counter = 0;
      analogWrite(LED_PIN_1,255);
    	lcd.setCursor(0, 0);
  		lcd.print("1: H");
      analogWrite(LED_PIN_2,255);
    	lcd.setCursor(0, 1);
  		lcd.print("2: H");
    
  }
  else {
    if (counter==clickCount * 10){ // set to *1 for debugging
       analogWrite(LED_PIN_1,0);
    	lcd.setCursor(0, 0);
  		lcd.print("1: L");
    }
    if (counter==clickCount * 30){ // set to *3 for debugging
      analogWrite(LED_PIN_2,0);
      lcd.setCursor(0, 1);
      lcd.print("2: L");
    }
    if (thirdLedCounter%3 == 0) {
      if(possibleChangeOfThirdLed) {
        possibleChangeOfThirdLed = 0;
        thirdLedState = !thirdLedState;

        if(thirdLedState) {
          analogWrite(LED_PIN_3, 255);
          lcd.setCursor(5, 0);
          lcd.print("3: H");
        } else {
          analogWrite(LED_PIN_3, 0);
          lcd.setCursor(5, 0);
          lcd.print("3: L");
        }
      }
    } else {
      possibleChangeOfThirdLed = 1;
    }
  }

}
