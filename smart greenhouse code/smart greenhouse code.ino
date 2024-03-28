#include <Wire.h>
#include <LiquidCrystal_I2C_Hangul.h>
LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);
#include "DHT.h"
#define DHTTYPE DHT11

const int DHTPin = 18;
const int soilpin = 33;
const int motorpin1 = 12;
const int motorpin2 = 14;
const int motorpin3 = 19;
const int motorpin4 = 5;
const int ldrpin = 13;

float Temperature;
int Humidity;
DHT dht(DHTPin, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("WELCOME");
  dht.begin();
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(motorpin3, OUTPUT);
  pinMode(motorpin4, OUTPUT);
  pinMode(ldrpin, INPUT);
  delay(4000);
  lcd.init();
  lcd.backlight();
  delay(200);
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME   ");
  delay(1000);
}

void readtemp()
{
  Temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(Temperature);
  delay(300);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(10, 0);
  lcd.print(Temperature);
  delay(1000);

  if (Temperature > 35)
  {
    Serial.println("High Temperature");
    motor2on();
  }

  else
  {
    Serial.println("Normal Temperature");
    motor2off();
  }

  Humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(Humidity);
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.setCursor(10, 1);
  lcd.print(Humidity);
  delay(1000);
  if (Humidity < 75)
  {
    Serial.println("High Humidity");
    motor3off();
  }

  else
  {
    Serial.println("Normal Humidity");
    motor2on();
  }
}

void readsoilsensor()
{
  int soilval = analogRead(soilpin);
  Serial.print("Soil: ");
  Serial.println(soilval);
  delay(300);

  if (soilval > 3500)
  {
    Serial.println("Dry Soil");
    delay(300);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dry Soil    ");

    delay(1000);
    motor1on();
  }
  else
  {
    Serial.println("Soil is WET");
    delay(300);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soil is WET  ");
    motor1off();
  }
  delay(1000);

}

void motor1on()
{
  digitalWrite(motorpin1, HIGH);
  delay(2000);

}

void motor1off()
{
  digitalWrite(motorpin1, LOW);
  delay(2000);
}

void motor2on()
{
  digitalWrite(motorpin2, HIGH);
  delay(2000);

}

void motor2off()
{
  digitalWrite(motorpin2, LOW);
  delay(2000);
}

void motor3on()
{
  digitalWrite(motorpin3, HIGH);
  delay(2000);

}

void motor3off()
{
  digitalWrite(motorpin3, LOW);
  delay(2000);
}

void motor4on()
{
  digitalWrite(motorpin4, HIGH);
  delay(2000);

}

void motor4off()
{
  digitalWrite(motorpin4, LOW);
  delay(2000);
}

void readldrsensor()
{

  int ldrval = digitalRead(ldrpin);
  if (ldrval == HIGH)
  {
    Serial.println("DARK");
    lcd.setCursor(0, 1);
    lcd.print("DARK          ");
    motor4on();

  }
  else
  {
    Serial.println("BRIGHT");
    lcd.setCursor(0, 1);
    lcd.print("BRIGHT          ");
    motor4off();
  }
}

void loop()
{
  readtemp();
  readsoilsensor();
  readldrsensor();

}
