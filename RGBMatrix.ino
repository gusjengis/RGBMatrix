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
  static const uint8_t register12[16] = {0, 1, 1, 1, 1, 1, 1, 1,
                                         1, 1, 1, 1, 1, 1, 1, 1};
  static const uint8_t register13[16] = {0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 1, 0, 0, 0, 0, 0, 0};

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
  // matrix.fillScreen(matrix.Color333(0, 0, 0));
  // for (uint8_t x = 0; x < 8; ++x) {
  //   for (uint8_t y = 0; y < 8; ++y) {
  //     matrix.drawPixel(x, y,
  //                      // matrix.Color333(max(x - y, 0), max(7 - (y + x), 0),
  //                      // max(x - y, 0)));
  //                      matrix.Color333(0, 0, max(x - y, 0)));
  //   }
  // }
}

void loop() {
  for (int16_t x = 0; x < 96; ++x) {
    // matrix.fillScreen(matrix.Color333(0, 0, 0));
    // matrix.drawRect(x - 2, 0, 1, 32, matrix.Color333(0, 0, 0));
    drawThing(x);
    int16_t z = x - 32;
    int16_t y = 12 + int16_t(sin(z / 5.0) * 8.0);
    matrix.drawRect(z, y, 1, 6, matrix.Color333(0, 0, 0));
    delay(1);
  }

  delay(4000);
}

void drawThing(int16_t x) {
  // if (x >= 0 && x < 64) {
  int16_t y = 12 + int16_t(sin(x / 5.0) * 8.0);
  matrix.drawRect(x, y, 1, 2, matrix.Color333(1, 0, 0));
  matrix.drawRect(x, y + 2, 1, 2, matrix.Color333(0, 1, 0));
  matrix.drawRect(x, y + 4, 1, 2, matrix.Color333(0, 0, 1));
  // }
}
