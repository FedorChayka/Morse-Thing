// Code for an installation which flashes a morse code message.

// Configuration:
#define LED_COUNT 200   // number of LEDs
#define LED_PIN 4       // pin to which WS2812 data is attached
#define DIT_LENGTH 100  // sets transmission speed; milliseconds
// this message is flashed on the LEDs:
char message[] = "CQ CQ CQ DE N7DUX N7DUX N7DUX K";


#include <FastLED.h>

CRGB leds[LED_COUNT];

const char* morseLetters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",  // A-J
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",    // K-T
  "..-", "...-", ".--", "-..-", "-.--", "--.."                            // U-Z
};
const char* morseNumbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."  // 0-9
};

#define DEBUG_ENABLE
// Debug Code:
#ifdef DEBUG_ENABLE
#define DEBUG_BEGIN(baudRate) Serial.begin(baudRate);
#define DEBUG(s) Serial.print(s);
#define DEBUGLN(t) Serial.println(t);
#else
#define DEBUG_BEGIN(baudRate)
#define DEBUG(s)
#define DEBUGLN(t)
#endif


void setup() {
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, LED_COUNT);
  ledsOFF();

  DEBUG_BEGIN(9600)
}

void loop() {
  for (uint8_t i = 0; message[i] != '\0'; i++){
    blinkChar(message[i]);
  }
  delay(3000); // delay between sending the message
}



void ledsON() {
  fill_solid(leds, LED_COUNT, CRGB(0, 7, 0));
  FastLED.show();
}

void ledsOFF() {
  fill_solid(leds, LED_COUNT, CRGB(0, 0, 0));
  FastLED.show();
}

void blinkDit() {
  ledsON();
  delay(DIT_LENGTH);
  ledsOFF();
  delay(DIT_LENGTH);
}

void blinkDah() {
  ledsON();
  delay(DIT_LENGTH * 3);
  ledsOFF();
  delay(DIT_LENGTH);
}

void blinkSpace() {
  ledsOFF();
  delay(DIT_LENGTH * 7);
}

void blinkChar(char c) {
  if (c == ' ') {
    blinkSpace();
    DEBUGLN("blinked space")
  } else if (c >= 65 && c <= 90) {

    DEBUG("blinked ASCII char ")
    DEBUG(c)
    DEBUG(", lookup no. ")
    DEBUG(c - 65)
    DEBUG(" ")
    DEBUGLN(morseLetters[c - 65]);
    DEBUG("i < ")
    DEBUGLN(strlen(morseLetters[c - 65]))

    for (uint8_t i = 0; i < strlen(morseLetters[c - 65]); i++) {
      if (morseLetters[c - 65][i] == '.') {
        blinkDit();
        DEBUGLN("blinked dit")
      } else if (morseLetters[c - 65][i] == '-') {
        blinkDah();
        DEBUGLN("blinked dah")
      } else {
        DEBUGLN("Error: unrecognized char in morseLetters lookup table")
      }
    }
    delay(DIT_LENGTH * 3);
  } else if (c >= 48 && c <= 57) {

    DEBUG("blinking ASCII char ")
    DEBUG(c)
    DEBUG(", lookup no. ")
    DEBUG(c - 48)
    DEBUG(" ")
    DEBUGLN(morseNumbers[c - 48]);
    DEBUG("i < ")
    DEBUGLN(strlen(morseNumbers[c - 48]))

    for (uint8_t i = 0; i < strlen(morseNumbers[c - 48]); i++) {
      if (morseNumbers[c - 48][i] == '.') {
        blinkDit();
        DEBUGLN("blinked dit")
      } else if (morseNumbers[c - 48][i] == '-') {
        blinkDah();
        DEBUGLN("blinked dah")
      } else {
        DEBUGLN("Error: unrecognized char in morseLetters lookup table")
      }
    }
    delay(DIT_LENGTH * 3);
  } else {
    DEBUGLN("Error: unknown character (not a capital letter or number")
  }
}
