#if defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)
#define ARDUINO_EXCLUDE_CODE
#endif // defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)

#ifndef ARDUINO_EXCLUDE_CODE

#include "command_responder.h"

#include "Arduino.h"

// Toggles the built-in LED every inference, and lights a colored LED depending
// on which word was detected.
void RespondToCommand(tflite::ErrorReporter *error_reporter,
                      int32_t current_time, const char *found_command,
                      uint8_t score, bool is_new_command)
{
    static bool is_initialized = false;
    if (!is_initialized)
    {
        pinMode(LED_BUILTIN, OUTPUT);
        // Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
        pinMode(LEDR, OUTPUT);
        pinMode(LEDG, OUTPUT);
        pinMode(LEDB, OUTPUT);
        // Ensure the LED is off by default.
        // Note: The RGB LEDs on the Arduino Nano 33 BLE Sense are on when the pin is LOW, off when HIGH.
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, HIGH);
        is_initialized = true;
    }
    static int32_t last_command_time = 0;
    static int count = 0;
    static int certainty = 220;

    if (is_new_command)
    {
        TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) @%dms", found_command,
                             score, current_time);
        // If we hear a command, light up the appropriate LED
        if (found_command[0] == 'o')
        {
            last_command_time = current_time;
            digitalWrite(LEDB, LOW);
            Serial.println("One!");
        }

        if (found_command[0] == 't' and found_command[1] == 'w')
        {
            last_command_time = current_time;
            digitalWrite(LEDB, LOW);
            Serial.println("Two!");
        }
        if (found_command[0] == 't' and found_command[1] == 'h')
        {
            last_command_time = current_time;
            digitalWrite(LEDB, LOW);
            Serial.println("Three!");
        }
        if (found_command[0] == 'f')
        {
            last_command_time = current_time;
            digitalWrite(LEDB, LOW);
            Serial.println("Four!");
        }
        if (found_command[0] == 'u')
        {
            last_command_time = current_time;
            Serial.print("Unknown!");
        }
    }

    // If last_command_time is non-zero but was >3 seconds ago, zero it
    // and switch off the LED.
    if (last_command_time != 0)
    {
        if (last_command_time < (current_time - 3000))
        {
            last_command_time = 0;
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDR, HIGH);
            digitalWrite(LEDG, HIGH);
            digitalWrite(LEDB, HIGH);
        }
        // If it is non-zero but <3 seconds ago, do nothing.
        return;
    }

    // Otherwise, toggle the LED every time an inference is performed.
    ++count;
    if (count & 1)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
}

#endif // ARDUINO_EXCLUDE_CODE
