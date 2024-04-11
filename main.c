#include <avr/io.h> // Assuming AVR microcontroller
#include <util/delay.h>
#include <stdint.h>
#include "hd44780.h"

#define outputA_pin PD6 // Arduino Pin 6
#define outputB_pin PD7 // Arduino Pin 7

int8_t counter = 0;
uint8_t aState;
uint8_t aLastState;
uint8_t bState;

void displayMenu() {
    uint8_t line;
    for (line = 0; line < 2; line++) {
        LCD_GotoXY(0, line);
        if (line == 0) {
            LCD_PrintString("Turn to see");
        } else {
            LCD_PrintString("current position");
        }
    }
    return;
}
void displayPosition(int8_t position) {
    LCD_Clear();
    LCD_PrintString("Position: ");
    LCD_GotoXY(11, 0);
    LCD_PrintInteger(position);
}
int main(void) {
    LCD_Setup(); // Initialize the LCD
    displayMenu();
    DDRD &= ~(1 << outputA_pin); // Set outputA pin as input
    DDRD &= ~(1 << outputB_pin); // Set outputB pin as input
    PORTD |= (1 << outputA_pin); // Enable pull-up resistor for outputA pin
    PORTD |= (1 << outputB_pin); // Enable pull-up resistor for outputB pin

    aLastState = PIND & (1 << outputA_pin);
    
    while (1) {
        // Read the current state of outputA and outputB pins
        aState = PIND & (1 << outputA_pin);
        bState = PIND & (1 << outputB_pin);
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
            }
            // Update the last state of outputA pin
            aLastState = aState;
            
        }
        return 0;
    }
