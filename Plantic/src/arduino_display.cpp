// Soil moisture display using the arduino nano and 

# include <Arduino.h>
#include <LiquidCrystal.h>

int soil_sensor = A0;
int sensorValue = 0;

int thresh_hold = 60;


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte smile[8] =
{
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b10001,
  0b01110,
  0b00000,
  0b00000
};

byte heart[8] = 
{
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.createChar(1, smile);
  lcd.createChar(2, heart);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(soil_sensor);
  // if(sensorValue > 800){
  //   Serial.print(sensorValue);
  //   Serial.print("|");
  //   Serial.println("Soil is dry");
  //   Serial.println("--------------------------------");
  // }
  // else if(sensorValue > 700 && sensorValue <= 800){
  //   Serial.print(sensorValue);
  //   Serial.print("|");
  //   Serial.println("Soil is moist");
  //   Serial.println("--------------------------------");
  // }
  // else if(sensorValue < 700){
  //   Serial.print(sensorValue);
  //   Serial.print("|");
  //   Serial.println("Soil is wet");
  //   Serial.println("--------------------------------");
  // }

  float moisture_percentage;
  moisture_percentage = ( 100 - ( (sensorValue/1023.00) * 100 ) );

  Serial.print("Sensor reading : ");
  Serial.println(sensorValue);
  Serial.print("Moisture % : ");
  Serial.println(moisture_percentage);
  Serial.println("---------------------------------");
  Serial.println("");


  if(moisture_percentage < thresh_hold){
    lcd.setCursor(0,1);
    lcd.print("Please water me");
    lcd.setCursor(15, 1);
    lcd.write(1);
  }
  else if(moisture_percentage > thresh_hold){
    lcd.setCursor(0,1);
    lcd.print("Dont water me");
    lcd.setCursor(15, 1);
    lcd.write(2);
  }

  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisture_percentage);
  lcd.print("%");

  delay(1000);
}