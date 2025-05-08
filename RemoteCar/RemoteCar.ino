// IN1 - kanal A PRZOD
// IN2 - kanal A TYL
//
// IN3 - kanal B PRZOD
// IN4 - kanal B TYL

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define MOTOR_A_PIN         2
#define MOTOR_A_REVERSE_PIN 3
#define MOTOR_B_PIN         4
#define MOTOR_B_REVERSE_PIN 5

#define SPEED_A_PIN 6
#define SPEED_B_PIN 6


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "47477";

int joystick_X, joystick_Y;
bool reverse = false;

void setup() {
  pinMode(MOTOR_A_PIN        , OUTPUT);
  pinMode(MOTOR_A_REVERSE_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN        , OUTPUT);
  pinMode(MOTOR_B_REVERSE_PIN, OUTPUT);

  // Sterowanie predkoscia
  pinMode(SPEED_A_PIN, OUTPUT);
  pinMode(SPEED_B_PIN, OUTPUT);
  // OPCJONALNE

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void parse_packet(char msg[32]){
  sscanf(msg, "%d %d", &joystick_X, &joystick_Y);

  joystick_X = map(joystick_X, 0, 1023, -255, 255);
  joystick_Y = map(joystick_Y, 0, 1023, -255, 255);

  if (joystick_X == -1){
    joystick_X = 0;
  }
  if(joystick_Y == -5){
    joystick_Y = 0;
  }
  reverse = false;

  joystick_X = map(joystick_X, -255, 255, 33, 123);
  

  if(joystick_Y<0){
    reverse = true;
    joystick_Y = abs(joystick_Y);
  }

  Serial.println("parsed x:");
  Serial.println(joystick_X);

  Serial.println("parsed y:");
  Serial.println(joystick_Y);

  Serial.println("Reverse:");
  Serial.println(reverse);

}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    parse_packet(text);
    delay(1000);
  }
  
  if(!reverse && joystick_Y){
    analogWrite(MOTOR_A_PIN,         HIGH);
    analogWrite(MOTOR_B_PIN,         HIGH);
    analogWrite(MOTOR_A_REVERSE_PIN , LOW);
    analogWrite(MOTOR_B_REVERSE_PIN , LOW);
  } else if (joystick_Y){
    analogWrite(MOTOR_A_PIN,         LOW);
    analogWrite(MOTOR_B_PIN,         LOW);
    analogWrite(MOTOR_A_REVERSE_PIN, HIGH);
    analogWrite(MOTOR_B_REVERSE_PIN, HIGH);
  } else {
    analogWrite(MOTOR_A_PIN,         LOW);
    analogWrite(MOTOR_B_PIN,         LOW);
    analogWrite(MOTOR_A_REVERSE_PIN, LOW);
    analogWrite(MOTOR_B_REVERSE_PIN, LOW);
  }

    analogWrite(MOTOR_A_PIN,         HIGH);
    analogWrite(MOTOR_B_PIN,         HIGH);
    analogWrite(MOTOR_A_REVERSE_PIN , HIGH);
    analogWrite(MOTOR_B_REVERSE_PIN , HIGH);
  //analogWrite(SPEED_A_PIN, joystick_Y);
  //analogWrite(SPEED_B_PIN, joystick_Y);

}
