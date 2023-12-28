#include <LiquidCrystal.h>
#include "DHT.h"
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
const int tempPin = 9;
const int lightPin = A1;
const float baselineTemp = 20;
const int buttonPin = 2;

#define DHTTYPE DHT22
#define DHTPIN 9
DHT dht(DHTPIN, DHTTYPE);

int currentState = 0;
static unsigned long last_interrupt_time = 0;



void changeState() {
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 100) {
    if (currentState == 2) {
      currentState = 0;
    } else {
      currentState++;
    }
    Serial.print("Interrupted state: ");
    Serial.println(currentState);
  }
  last_interrupt_time = interrupt_time;
}

void setup() {
  ///code for temperature sensor
  Serial.begin(9600);


  pinMode(buttonPin, INPUT);
  pinMode(DHTPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeState, RISING);

  lcd.begin(16, 2);
  dht.begin();
  pinMode(lightPin, INPUT);
}

int lightSensorValue = 0;
int lightVal = 0;

int readLight() {
  lightSensorValue = analogRead(lightPin);
  lightVal = lightSensorValue / 4;
  return lightSensorValue;
}

float readTemperature() {

  // float h = dht.readHumidity();
  float t = dht.readTemperature();
  return t;
}

float readHumidity() {
  float h = dht.readHumidity();
  return h;
}

void printTemp(float temp) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.print("C");
}

void printLight(int light) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light value:");
  lcd.setCursor(0, 1);
  lcd.print(light);
}

void printHumidity(float humidity) {
  Serial.print("Humidity: ");
  Serial.println(humidity);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.setCursor(0, 1);
  lcd.print(humidity);
}




void loop() {
  ///tempearture


  // int reading = digitalRead(buttonPin);
  // if (reading == HIGH) {

  // }
  switch (currentState) {
    case 0:
      //Temperature
      printTemp(readTemperature());
      break;
    case 1:
      printLight(readLight());
      break;
    case 2:
      printHumidity(readHumidity());
      break;
    default:
      break;
  }

  // readLight();

  // float temp = readTemperature();

  // printTemp(temp);

  // Serial.println(reading);


  delay(2000);
  // put your main code here, to run repeatedly:
}
