#include <Keypad.h>
#include <string.h>

#include "pins.h"

const byte ROWS     = 0x4; // Amount of rows on the keypad
const byte COLS     = 0x4; // Amount of columns on the keypad
const int  PIN_SIZE = 4;

// The actual keys on the keypad
const char keypadMap[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

// The pins for the rows (left 4 pins)
const byte rowPins[ROWS] = {
    0x09, 0x08, 0x07, 0x06
};

// The pins for the cols (right 4 pins)
const byte colPins[COLS] = {
    0x05, 0x04, 0x03, 0x02
};

// Initialize the keypad obj
Keypad keypad = Keypad(
    makeKeymap(keypadMap),
    rowPins,
    colPins,
    ROWS,
    COLS
);

void setup() {
    Serial.begin(9600); // Initialize the serial connection
}

int counter = 0;    // The temporary pin counter
char pin[PIN_SIZE]; // The temporary pin

void loop() {
    char readKey = keypad.getKey(); // Read a key

    if (readKey) { // If the key is not null
        // Increment the counter and set the temp pin accordingly
        pin[counter] = readKey;
        counter++;

        Serial.println(readKey);
        
        if (counter == (PIN_SIZE)) {
            checkPin(pin); // Check if the pin is valid
            
            // Reset the pin and counter
            counter = 0;
        }
        
    }
}

// checkPin - Check if a pin is valid
void checkPin(char *pin) {
    boolean secure = false; // Whether a valid pin was entered or not

    // Loop through all of the valid pins
    for (int j = 0; j < VALID_PIN_COUNT; j++) {
        int match = 0;
        // Compare the two char arrays
        for (int k = 0; k < PIN_SIZE; k++) {
            // Serial.print("match: ");
            // Serial.println(match);

            // Compare the chars
            if (validPins[j][k] == pin[k]) {
                match++;
            }
        }

        // See if there is a match
        if (match == PIN_SIZE) {
            secure = true;
            break;
        }
        
    }

    if (secure) {
        Serial.println("Valid pin entered!");
    }

    else {
        Serial.println("Invalid pin entered!");
    }

}
