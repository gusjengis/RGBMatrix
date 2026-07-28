#include <RGBmatrixPanel.h>

#define CLK 11
#define LAT 10
#define OE 9
#define A A0
#define B A1
#define C A2
#define D A3

// On the Mega, this library uses fixed RGB data pins 24 through 29.
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

static void writePanelRegister(const uint8_t config[16], uint8_t latchClocks) {
  for (uint8_t column = 0; column < 64; ++column) {
    const uint8_t data = config[column & 0x0f] ? HIGH : LOW;
    for (uint8_t pin = 24; pin <= 29; ++pin) {
      digitalWrite(pin, data);
    }

    digitalWrite(LAT, column > 64 - latchClocks ? HIGH : LOW);
    digitalWrite(CLK, HIGH);
    delayMicroseconds(2);
    digitalWrite(CLK, LOW);
  }

  digitalWrite(LAT, LOW);
}

static void initializePanelDriver() {
  // Waveshare's P5 panel needs these FM612x control registers before refresh.
  static const uint8_t register12[16] = {
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  static const uint8_t register13[16] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};

  for (uint8_t pin = 24; pin <= 29; ++pin) {
    pinMode(pin, OUTPUT);
  }
  pinMode(CLK, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);
  digitalWrite(LAT, LOW);
  digitalWrite(CLK, LOW);

  writePanelRegister(register12, 12);
  writePanelRegister(register13, 13);
}

void setup() {
  initializePanelDriver();
  matrix.begin();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.drawPixel(32, 16, matrix.Color333(7, 7, 7));
}

void loop() {
}
