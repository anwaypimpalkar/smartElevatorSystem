#if defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)
#define ARDUINO_EXCLUDE_CODE
#endif // defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)

#ifndef ARDUINO_EXCLUDE_CODE

#include "detection_responder.h"

#include "Arduino.h"

bool RespondToKWS(tflite::ErrorReporter *error_reporter, const char *found_command, bool is_new_command, int8_t score)
{
  if (!is_initialized)
  {
    pinMode(LED_BUILTIN, OUTPUT);
    // Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    is_initialized = true;
  }

  // Ensure the LED is off.
  // Note: The RGB LEDs on the Arduino Nano 33 BLE
  // Sense are on when the pin is LOW, off when HIGH.
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  static int count = 0; //static so only initialize the first time

  if (is_new_command)
  {
    TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (score: %d)", found_command,
                         score);
    // If we hear a command, light up the appropriate LED
    if (found_command[0] == 'y')
    {
      digitalWrite(LEDB, LOW); // Blue for yes
      Serial.print("Yes!");
      return true;
    }

    if (found_command[0] == 'n')
    {
      digitalWrite(LEDR, LOW); // Red for no
      Serial.print("No!");
    }
  }
  //toggle yellow side LED everytime a micro_speech inference is performed
  ++count;
  if (count & 1)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  return false;
}

// Flash the blue LED after each inference
void RespondToDetection(tflite::ErrorReporter *error_reporter,
                        int8_t person_score, int8_t no_person_score)
{
  if (!is_initialized)
  {
    // Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    is_initialized = true;
  }

  // Note: The RGB LEDs on the Arduino Nano 33 BLE
  // Sense are on when the pin is LOW, off when HIGH.

  // Switch the person/not person LEDs off
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDB, HIGH);

  // Switch on the green LED when a person is detected,
  // the red when no person is detected
  if (person_score > no_person_score)
  {
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDR, HIGH);
  }
  else
  {
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDR, LOW);
  }

  TF_LITE_REPORT_ERROR(error_reporter, "Person score: %d No person score: %d",
                       person_score, no_person_score);
}

#endif // ARDUINO_EXCLUDE_CODE
