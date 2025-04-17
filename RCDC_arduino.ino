
const int BUTTON_PIN = 2
const int LED_PIN_1 = 3
const int LED_PIN_2 = 5


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(BUTTON_PIN, INPUT_PULLUP);
}



void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState==1)
    {
       analogWrite(LED_PIN_1,255);
       analogWrite(LED_PIN_2,255);
       delay(10000);
       analogWrite(LED_PIN_1,0);
       delay(20000)
       analogWrite(LED_PIN_2,0);
    }
    
}
