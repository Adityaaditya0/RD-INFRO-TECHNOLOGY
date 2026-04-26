#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object (address may be 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Welcome message
  lcd.print("Temp Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  // LED Pins
  pinMode(8, OUTPUT);   // Red LED
  pinMode(9, OUTPUT);   // Green LED
  pinMode(10, OUTPUT);  // Yellow LED

  pinMode(A0, INPUT);   // Temperature sensor

  delay(2000);
  lcd.clear();
}

void loop()
{
  int sensor_value = analogRead(A0);

  // Convert to voltage
  float Voltage = (sensor_value / 1023.0) * 5.0;

  // LM35 formula
  float Temperature_C = (Voltage - 0.5) * 100.0;

  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(Temperature_C, 1);
  lcd.print(" C");

  // Clear second line
  lcd.setCursor(0, 1);
  lcd.print("                "); // clear line

  lcd.setCursor(0, 1);

  if (Temperature_C <= 10)
  {
    digitalWrite(10, HIGH); // Yellow
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    lcd.print("Too Cold!!");
  }
  else if (Temperature_C > 10 && Temperature_C <= 35)
  {
    digitalWrite(9, HIGH); // Green
    digitalWrite(10, LOW);
    digitalWrite(8, LOW);
    lcd.print("Perfect Temp");
  }
  else
  {
    digitalWrite(8, HIGH); // Red
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    lcd.print("Too Hot!!");
  }

  delay(500);
}
