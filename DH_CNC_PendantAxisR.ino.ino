#include <Bounce.h>
#include <Encoder.h>

#define PIN_LED_X     16
#define PIN_LED_Y     15
#define PIN_LED_Z     14
#define PIN_LED_FAST  17
#define PIN_LED_1MM   18
#define PIN_LED_01MM  19
#define PIN_LED_001MM 20
#define PIN_BTN_X     4
#define PIN_BTN_Y     3
#define PIN_BTN_Z     2
#define PIN_BTN_FAST  5
#define PIN_BTN_1MM   6
#define PIN_BTN_01MM  7
#define PIN_BTN_001MM 8
#define PIN_ENC_A     9
#define PIN_ENC_B     10

enum axis {
  X_AXISr,
  Y_AXISr,
  Z_AXISr
};

enum speed {
  SPD_FAST,
  SPD_1MM,
  SPD_01MM,
  SPD_001MM
};

Bounce buttonX = Bounce(PIN_BTN_X, 10);
Bounce buttonY = Bounce(PIN_BTN_Y, 10);
Bounce buttonZ = Bounce(PIN_BTN_Z, 10);
Bounce buttonFast = Bounce(PIN_BTN_FAST, 10);
Bounce button1MM = Bounce(PIN_BTN_1MM, 10);
Bounce button01MM = Bounce(PIN_BTN_01MM, 10);
Bounce button001MM = Bounce(PIN_BTN_001MM, 10);
Encoder encoderScroll(PIN_ENC_A, PIN_ENC_B);

enum axis activeAxis = X_AXISr;
enum axis lastAxis = Z_AXISr;
int lastAxisLED = PIN_LED_X;
int lastSpeedLED = PIN_LED_001MM;
enum speed activeSpeed = SPD_FAST;
enum speed lastSpeed = SPD_01MM;
int lastScrollPos = -999;
int scrollDelta = 0;

void setup() {

  for (int ii = 2; ii < 11; ii++) pinMode(ii, INPUT_PULLUP);
  for (int ii = 14; ii < 21; ii++) pinMode(ii, OUTPUT);
  digitalWrite(PIN_LED_X, HIGH);
  digitalWrite(PIN_LED_FAST, HIGH);
  //Serial.begin(9600);
    
}

void loop() { // ******************************** BEGIN MAIN LOOP ********************************
  
  buttonX.update();
  buttonY.update();
  buttonZ.update();
  buttonFast.update();
  button1MM.update();
  button01MM.update();
  button001MM.update();

  if (buttonX.fallingEdge()) {
    activeAxis = X_AXISr;
    //Serial.println("X");
  }
  if (buttonY.fallingEdge()) {
    activeAxis = Y_AXISr;
    //Serial.println("Y");
  }
  if (buttonZ.fallingEdge()) {
    activeAxis = Z_AXISr;
    //Serial.println("Z");
  }
  if (buttonFast.fallingEdge()) {
    activeSpeed = SPD_FAST;
  }
  if (button1MM.fallingEdge()) {
    activeSpeed = SPD_1MM;
  }
  if (button01MM.fallingEdge()) {
    activeSpeed = SPD_01MM;
  }
  if (button001MM.fallingEdge()) {
    activeSpeed = SPD_001MM;
  }

  long newScrollPos = encoderScroll.read();
  
  if (abs(newScrollPos - lastScrollPos) >= 4) { // there are roughly four presses detected from each rotation to the next detent
    if (newScrollPos - lastScrollPos > -1){ // positive increase
      switch(activeAxis){
      case X_AXISr:
        Keyboard.press(KEY_RIGHT);
        Keyboard.release(KEY_RIGHT);
      break;
      case Y_AXISr:
        Keyboard.press(KEY_UP);
        Keyboard.release(KEY_UP);
      break;
      case Z_AXISr:
        Keyboard.press(KEY_PAGE_UP);
        Keyboard.release(KEY_PAGE_UP);
      } 
    } else {
      switch(activeAxis){
      case X_AXISr:
        Keyboard.press(KEY_LEFT);
        Keyboard.release(KEY_LEFT);
      break;
      case Y_AXISr:
        Keyboard.press(KEY_DOWN);
        Keyboard.release(KEY_DOWN);
      break;
      case Z_AXISr:
        Keyboard.press(KEY_PAGE_DOWN);
        Keyboard.release(KEY_PAGE_DOWN);
      }
    }
    lastScrollPos = newScrollPos;
  }
  
  if (activeAxis != lastAxis){
    digitalWrite(lastAxisLED, LOW);
    switch(activeAxis){
      case X_AXISr:
        digitalWrite(PIN_LED_X, HIGH);
        lastAxisLED = PIN_LED_X;
      break;
      case Y_AXISr:
        digitalWrite(PIN_LED_Y, HIGH);
        lastAxisLED = PIN_LED_Y;
      break;
      case Z_AXISr:
        digitalWrite(PIN_LED_Z, HIGH);
        lastAxisLED = PIN_LED_Z;
      break;
    }
    lastAxis = activeAxis;
  }

  if (activeSpeed != lastSpeed){
    digitalWrite(lastSpeedLED, LOW);
    switch(activeSpeed){
      case SPD_FAST:
        Keyboard.press(KEY_4);
        Keyboard.release(KEY_4);
        digitalWrite(PIN_LED_FAST, HIGH);
        lastSpeedLED = PIN_LED_FAST;
      break;
      case SPD_1MM:
        Keyboard.press(KEY_3);
        Keyboard.release(KEY_3);
        digitalWrite(PIN_LED_1MM, HIGH);
        lastSpeedLED = PIN_LED_1MM;
      break;
      case SPD_01MM:
        Keyboard.press(KEY_2);
        Keyboard.release(KEY_2);
        digitalWrite(PIN_LED_01MM, HIGH);
        lastSpeedLED = PIN_LED_01MM;
      break;
      case SPD_001MM:
        Keyboard.press(KEY_1);
        Keyboard.release(KEY_1);
        digitalWrite(PIN_LED_001MM, HIGH);
        lastSpeedLED = PIN_LED_001MM;
      break;
    }
    lastSpeed = activeSpeed;
  }
  
} // ******************************** END MAIN LOOP ********************************
