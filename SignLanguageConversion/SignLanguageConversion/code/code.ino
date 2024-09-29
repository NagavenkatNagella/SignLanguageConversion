#include "SoftwareSerial.h"
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial(3, 2);  // RX, TX for Bluetooth
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the LCD

#define blue 5    // Changed pins to avoid conflict with SoftwareSerial
#define green 6
#define red 7

unsigned int f;
unsigned int g;
unsigned int h;
unsigned int toilet;  // Variable for A0 (toilet sensor)

void setup() {
  // Initialize pin modes
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  // Begin serial communication
  Serial.begin(9600);   // For Serial Monitor
  mySerial.begin(9600); // For Bluetooth communication

  // Initialize the LCD
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("  Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("Sign Converstion");
  delay(3000);
  lcd.clear();
}

void loop() {
  // Read sensor values
  toilet = analogRead(0);  // Reading from A0
  f = analogRead(1);
  g = analogRead(2);
  h = analogRead(3);

  // Debugging - print sensor values to Serial Monitor
  Serial.print("toilet: "); Serial.println(toilet);
  Serial.print("f: "); Serial.println(f);
  Serial.print("g: "); Serial.println(g);
  Serial.print("h: "); Serial.println(h);

  // Adjusted thresholds based on sensor values
  // Condition for "I want to go to toilet"
  if (toilet < 1020) {  // Adjusted threshold for toilet sensor
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    
    // Send message via Bluetooth
    mySerial.println("I want to go to toilet");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I want to go to");
    lcd.setCursor(0, 1);
    lcd.print("   the toilet");

    delay(3000);  // Keep the message on screen for 3 seconds
    
    // Reset display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" If Anything");
    lcd.setCursor(0, 1);
    lcd.print("  You Want ");
  }
  // Condition for "Plz Give Me Water"
  else if (f < 1020) {  // Adjusted threshold for 'f' sensor
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);

    // Send message via Bluetooth
    mySerial.println("Plz Give Me Water");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Plz Give Me");
    lcd.setCursor(0, 1);
    lcd.print("     Water   ");
    
    delay(3000);  // Keep the message on screen for 3 seconds
    
    // Reset display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" If Anything");
    lcd.setCursor(0, 1);
    lcd.print("  You Want ");
  }
  // Condition for "Plz Give Me Food"
  else if (g < 1020) {  // Adjusted threshold for 'g' sensor
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);

    // Send message via Bluetooth
    mySerial.println("Plz Give Me Food");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Plz Give Me ");
    lcd.setCursor(0, 1);
    lcd.print("     Food   ");
    
    delay(3000);  // Keep the message on screen for 3 seconds
    
    // Reset display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" If Anything");
    lcd.setCursor(0, 1);
    lcd.print("  You Want ");
  }
  // Condition for "Plz Give Me Tea"
  else if (h < 1020) {  // Adjusted threshold for 'h' sensor
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);

    // Send message via Bluetooth
    mySerial.println("Plz Give Me Tea");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Plz Give Me");
    lcd.setCursor(0, 1);
    lcd.print("     Tea   ");
    
    delay(3000);  // Keep the message on screen for 3 seconds
    
    // Reset display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" If Anything");
    lcd.setCursor(0, 1);
    lcd.print("  You Want ");
  } else {
    // No specific condition met
    Serial.println("No specific condition met.");

    // Display default message on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Everything is OK!");
    delay(3000);  // Keep the default message for 3 seconds
  }

  // Short delay between loops to avoid overload
  delay(200);
}
