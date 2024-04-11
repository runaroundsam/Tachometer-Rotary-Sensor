#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define outputA_pin 6 // Arduino Pin 6
#define outputB_pin 7 // Arduino Pin 7
#define outputC_pin 8 // Arduino Pin 7
int8_t counter = 0;
uint8_t aState;
uint8_t aLastState;
uint8_t bState;
uint8_t cState;

void displayMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Turn to see");
    lcd.setCursor(0, 1);
    lcd.print("current position");
}

void displayPosition(int8_t position) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Position: ");
    lcd.setCursor(11, 0);
    lcd.print(position);
}

void setup() {
    Serial.begin(9600); 
    lcd.init();
    lcd.backlight();
    displayMenu();
    pinMode(outputA_pin, INPUT); // Set outputA pin as input
    pinMode(outputB_pin, INPUT); // Set outputB pin as input
    pinMode(outputC_pin, INPUT); // Set outputC pin as input

    aLastState = digitalRead(outputA_pin); // Read initial state of A
}

void loop() {
    // Read the current state of outputA, outputB, outputC pins
    aState = digitalRead(outputA_pin);
    bState = digitalRead(outputB_pin);
    cState = digitalRead(outputC_pin);
    
    // Check for a change in state of outputA pin
    if (aState != aLastState) {
        // If the state is still changed, update the counter based on the direction of rotation
        if (bState != aState) {
            counter++; // Clockwise rotation
        } else {
            counter--; // Counterclockwise rotation
        }
        // Update the LCD display with the new position
        displayPosition(counter);
        // Output the counter value to the Serial Monitor
        Serial.println(counter);
    }
    // Check if button is pressed
    if (cState == LOW) {
        counter = 0;
        displayPosition(counter);
        Serial.println(counter);
    }
    // Update the last state of outputA pin
    aLastState = aState;
}