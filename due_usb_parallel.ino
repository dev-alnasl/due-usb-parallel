/**
 * @file   due_usb_parallel.ino
 * @author alnasl <dev-alnasl@mono-wireless.com>
 * @date   Thu Dec 12 14:35:20 2024
 *
 * @brief  Use Arduino Due as 3.3V Parallel I/O Converter via USB MIDI
 *
 * Copyright (C) 2025 Mono Wireless Inc. All Rights Reserved.
 * Released under MW-OSSLA-*J,*E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT).
 */

#include <USB-MIDI.h>

USBMIDI_CREATE_DEFAULT_INSTANCE();

#define PWM0 2
#define PWM11 13
#define DO0 14
#define DO19 33
#define DI0 34
#define DI19 53
#define AI0 54
#define AI11 65
#define AO0 66
#define AO1 67

#define INPUT_CHECK_PERIOD 20 // ms
#define AI_THRESH 31  // Requires at lease about 25mV changes

static bool DigitalInputValues[20];
static uint16_t AnalogInputValues[12];

void setup() {
    // UART
    Serial.begin(115200);
    while (!Serial) {}

    // MIDI
    Serial.println("Starting MIDI over Native USB...");
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn(onNoteOn);
    MIDI.setHandleNoteOff(onNoteOff);
    MIDI.setHandleControlChange(onControlChange);

    // PWM
    analogWriteResolution(12);
    for (int pwm = PWM0; pwm <= PWM11; pwm++) {
        analogWrite(pwm, 0);
    }

    // DO
    for (int dout = DO0; dout <= DO19; dout++) {
        pinMode(dout, OUTPUT);
        digitalWrite(dout, HIGH); // Initial HIGH (3.3V)
    }

    // DI
    for (int di = DI0; di <= DI19; di++) {
        DigitalInputValues[di-DI0] = false;
        pinMode(di, INPUT_PULLUP);
    }

    // AI
    analogReadResolution(12);
    for (int ai = AI0; ai <= AI11; ai++) {
        AnalogInputValues[ai-AI0] = 0;
    }

    // AO
    analogWriteResolution(12);
}

void loop() {
    static uint32_t last_update = 0;

    if (millis() - last_update > INPUT_CHECK_PERIOD) {
        // DI
        for (int di = DI0; di <= DI19; di++) {
            bool current_value = (digitalRead(di) == LOW);
            if (current_value != DigitalInputValues[di-DI0]) {
                if (current_value) {
                    MIDI.sendNoteOn(di, 100, 1);
                } else {
                    MIDI.sendNoteOff(di, 0, 1);
                }
                DigitalInputValues[di-DI0] = current_value;
            }
        }

        // AI
        for (int ai = AI0; ai <= AI11; ai++) {
            uint16_t current_value = analogRead(ai);
            if (abs(current_value - AnalogInputValues[ai-AI0]) > AI_THRESH) {
                Serial.print("\n[");
                Serial.print(ai-AI0, DEC);
                Serial.print("] current: ");
                Serial.print(current_value, DEC);
                Serial.print(", previous: ");
                Serial.print(AnalogInputValues[ai-AI0], DEC);
                Serial.print(", abs: ");
                Serial.print(abs(current_value - AnalogInputValues[ai-AI0]), DEC);
                Serial.print(", thresh: ");
                Serial.print(AI_THRESH, DEC);

                MIDI.sendControlChange(ai, current_value / 32, 1);
                AnalogInputValues[ai-AI0] = current_value;
            }
        }

        last_update = millis();
    }

    // MIDI
    MIDI.read();
}

void onNoteOn(byte channel, byte note, byte velocity) {
    Serial.print("[debug] Note On received: ");
    Serial.print("Note = ");
    Serial.print(note);
    Serial.print(", Velocity = ");
    Serial.print(velocity);
    Serial.print(", Channel = ");
    Serial.println(channel);

    if (DO0 <= note and note <= DO19) {
        // DO
        digitalWrite(note, LOW);
    } else {
        Serial.println("Not a DO pin number");
    }
}

void onNoteOff(byte channel, byte note, byte velocity) {
    Serial.print("[debug] Note Off received: ");
    Serial.print("Note = ");
    Serial.print(note);
    Serial.print(", Channel = ");
    Serial.println(channel);

    if (DO0 <= note and note <= DO19) {
        // DO
        digitalWrite(note, HIGH);
    } else {
        Serial.println("Not a DO pin number");
    }
}

void onControlChange(byte channel, byte control, byte value) {
  Serial.print("[debug] Channel: ");
  Serial.print(channel);
  Serial.print(", Control: ");
  Serial.print(control);
  Serial.print(", Value: ");
  Serial.println(value);

  if (PWM0 <= control and control <= PWM11) {
      // PWM
      analogWrite(control, value * 2);
  } else if (AO0 <= control and control <= AO1) {
      // AO
      analogWrite(control, value * 32);
  } else {
      Serial.println("Not a AO or PWM pin number");
  }
}
