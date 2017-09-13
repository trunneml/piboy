#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 7;
const int pinButtonS = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinButtonS, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.

  Gamepad.begin();
  System.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Press button 1-32
    static uint8_t count = 0;
    count++;
    if (count == 33) {
      Gamepad.releaseAll();
      count = 0;
    }
    else
      Gamepad.press(count);

    // Move x/y Axis to a new position (16bit)
    Gamepad.xAxis(random(0xFFFF));
    Gamepad.yAxis(random(0xFFFF));

    // Go through all dPad positions
    // values: 0-8 (0==centered)
    static uint8_t dpad1 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad1(dpad1++);
    if (dpad1 > GAMEPAD_DPAD_UP_LEFT)
      dpad1 = GAMEPAD_DPAD_CENTERED;

    static int8_t dpad2 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad2(dpad2--);
    if (dpad2 < GAMEPAD_DPAD_CENTERED)
      dpad2 = GAMEPAD_DPAD_UP_LEFT;

    // Functions above only set the values.
    // This writes the report to the host.
    Gamepad.write();

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
 
  if (!digitalRead(pinButtonS)) {
    digitalWrite(pinLed, HIGH);

    // Puts PC into sleep mode/shuts it down
    //System.write(SYSTEM_SLEEP);
    System.write(SYSTEM_POWER_DOWN);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
