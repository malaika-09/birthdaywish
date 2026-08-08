BIRTHDAY COUNTDOWN PROJECT - ESP32 + 1.3" SH1106 OLED VERSION
  -----------------------------------------------------------------
  Hardware:
  - ESP32 Dev Board
  - OLED 1.3" SH1106 (I2C) -> SDA:21, SCL:22, VCC:3.3V, GND:GND
  - Buzzer -> GPIO 4
  - Button -> Built-in BOOT button (GPIO 0) -- no extra wiring required
  - 5 LEDs -> GPIO 18, 19, 17, 16, 15

  Library: "Adafruit SH110X" (install from Library Manager)

  Working:
  1. BOOT button press -> OLED shows running countdown (10 to 0) , LEDs start to chase 
  2. Countdown ends -> Buzzer beep + all LEDs blink
  3. "Happy Birthday" tune starts, OLED give message + LEDs disco effect
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 4
#define BUTTON_PIN 0   // Built-in BOOT button

int ledPins[] = {18, 19, 17, 16, 15};
int numLeds = 5;

// Happy Birthday tune notes (Hz)
int melody[] = {
  262, 262, 294, 262, 349, 330,
  262, 262, 294, 262, 392, 349,
  262, 262, 523, 440, 349, 330, 294,
  466, 466, 440, 349, 392, 349
};
int noteDurations[] = {
  8, 8, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 2
};

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // 0x3C address for SH1106  (0x78 ka 7-bit form)
  if (!display.begin(0x3C, true)) {
    Serial.println("OLED not found!");
    while (true);
  }

  display.setRotation(0);
  showStartScreen();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(200); // debounce
    startCountdown();
  }
}

void showStartScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 20);
  display.println("Press BOOT to");
  display.setCursor(15, 35);
  display.println("Start Countdown");
  display.display();
}

void startCountdown() {
  for (int i = 10; i >= 0; i--) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(20, 10);
    display.println("Countdown");
    display.setTextSize(4);
    display.setCursor(50, 35);
    display.println(i);
    display.display();

    // one LED chase in one second
    digitalWrite(ledPins[i % numLeds], HIGH);
    tone(BUZZER_PIN, 1000, 100);
    delay(400);
    digitalWrite(ledPins[i % numLeds], LOW);
    delay(600);
  }

  // Time's up
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(15, 25);
  display.println("Time's Up!");
  display.display();

  for (int i = 0; i < 3; i++) {
    allLeds(HIGH);
    tone(BUZZER_PIN, 1500, 300);
    delay(300);
    allLeds(LOW);
    delay(200);
  }

  playHappyBirthdayWithLights();

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(5, 15);
  display.println("HAPPY");
  display.setCursor(5, 40);
  display.println("BIRTHDAY!");
  display.display();

  // disco LED effect 
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(80);
      digitalWrite(ledPins[i], LOW);
    }
  }

  // Name screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(15, 25);
  display.println("name....");
  display.display();

  startTime = millis();
  while (millis() - startTime < 3000) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(80);
      digitalWrite(ledPins[i], LOW);
    }
  }

  delay(1000);
  showStartScreen();
}

void allLeds(bool state) {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], state);
  }
}

void playHappyBirthdayWithLights() {
  int size = sizeof(melody) / sizeof(int);
  for (int note = 0; note < size; note++) {
    int duration = 1000 / noteDurations[note];
    tone(BUZZER_PIN, melody[note], duration);

    // note bajte waqt LED jalao
    digitalWrite(ledPins[note % numLeds], HIGH);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    digitalWrite(ledPins[note % numLeds], LOW);
    noTone(BUZZER_PIN);
  }
}
