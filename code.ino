#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C address (adjust if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define DHTPIN 2       
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

const int greenLED = 3;
const int yellowLED = 4;
const int redLED = 5;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  lcd.backlight();
  
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C  ");

  if (temp <= 20) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: Cold     ");
  } else if (temp <= 30) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: Warm     ");
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Status: Hot      ");
  }

  delay(2000);
}
