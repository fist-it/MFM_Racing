/* 
PINOUT
D7 - CE
D8 - CSN
D11 - MOSI
D12 - MISO
D13 - SCK
*/

#define XPIN A0
#define YPIN A1
#define SWPIN A2 

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int cor_X;
int cor_Y;
char msg[32] = "";

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "47477";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(XPIN, INPUT);
  pinMode(YPIN, INPUT);
  pinMode(SWPIN, INPUT_PULLUP);
  Serial.println("Setup");
}

void loop() {
  cor_X = analogRead(XPIN);
  cor_Y = analogRead(YPIN);
  snprintf(msg, sizeof(msg),"%d %d", cor_X ,cor_Y);
  Serial.println(msg);

  radio.write(&msg, sizeof(msg));
  delay(1000);
  
}
