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

static const uint8_t COLUMNS = 10;
static const uint8_t ROWS = 4;
static const uint8_t TEXT_CAPACITY = 160;
static char text[TEXT_CAPACITY];
static uint8_t textLength = 0;

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

static void drawText() {
  char lines[ROWS][COLUMNS + 1] = {};
  uint8_t line = 0;
  uint8_t column = 0;

  for (uint8_t i = 0; i < textLength; ++i) {
    if (text[i] == '\n') {
      ++line;
      column = 0;
      memset(lines[line % ROWS], 0, COLUMNS + 1);
      continue;
    }

    lines[line % ROWS][column++] = text[i];
    if (column == COLUMNS) {
      ++line;
      column = 0;
      memset(lines[line % ROWS], 0, COLUMNS + 1);
    }
  }

  const uint8_t firstLine = line >= ROWS ? line - ROWS + 1 : 0;
  matrix.fillScreen(0);
  for (uint8_t row = 0; row < ROWS && firstLine + row <= line; ++row) {
    matrix.setCursor(0, row * 8);
    matrix.print(lines[(firstLine + row) % ROWS]);
  }
}

static void appendCharacter(char character) {
  if (textLength == TEXT_CAPACITY) {
    memmove(text, text + 1, TEXT_CAPACITY - 1);
    --textLength;
  }
  text[textLength++] = character;
}

static bool processSerialInput(char character) {
  if (character == '\b' || character == 0x7f) {
    if (textLength > 0) {
      --textLength;
      return true;
    }
    return false;
  }
  if (character == '\r' || character == '\n') {
    appendCharacter('\n');
    return true;
  }
  if (character >= ' ' && character <= '~') {
    appendCharacter(character);
    return true;
  }
  return false;
}

void setup() {
  initializePanelDriver();
  matrix.begin();
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color333(1, 1, 1));
  drawText();

  Serial.begin(115200);
  Serial.println(F("RGBMatrix ready"));
}

void loop() {
  bool changed = false;
  while (Serial.available() > 0) {
    changed |= processSerialInput(Serial.read());
  }

  if (changed) {
    drawText();
  }
}
