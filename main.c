#include <Adafruit_NeoPixel.h>
#define PIXELSPIN      0
#define NUMPIXELS      2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELSPIN, NEO_GRB + NEO_KHZ800);

// both digital and analog pins 1 are used
#define INPUT_PIN 1

int value;

int r;
int g;
int b;

// store state if button was pressed
int colorChanged = 0;

// how much to subtract from the analog input value
int calibration = 935;

void randColors() {
  r = random(0, 256);
  g = random(0, 256);
  b = random(0, 256);
}

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pixels.begin(); // This initializes the NeoPixel library.
  randColors();
}

void loop() {
  value = constrain((analogRead(INPUT_PIN) - calibration), 0, 255);
  
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(0, pixels.Color(value * (r / 255.0), value * (g / 255.0), value * (b / 255.0)));
    pixels.show();
  }
  
  if(digitalRead(INPUT_PIN) && !colorChanged) {
    randColors();
    colorChanged = 1;
  } else if (!digitalRead(INPUT_PIN)) {
    colorChanged = 0;
  }
}
