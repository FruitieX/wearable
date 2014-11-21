#include <Adafruit_NeoPixel.h>
// digital pin 1
#define PIXELSPIN      1
#define NUMPIXELS      4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELSPIN, NEO_GRB + NEO_KHZ800);

// analog pin 1
#define INPUT_PIN 1
// digital pin 0
#define CHANGE_PIN 0

int value;

int r;
int g;
int b;

// store state if button was pressed
int colorChanged = 0;

// how much to subtract from the analog input value
int calibration = 645;

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

int avgVal = 0;
int vals[4] = {0};

void loop() {
  value = constrain((analogRead(INPUT_PIN) - calibration) * 10, 0, 255);

  avgVal = 0.9 * avgVal + 0.1 * value;
  
  vals[0] = constrain(avgVal * 4, 0, 255);
  vals[1]= constrain((avgVal - 64) * 4, 0, 255);
  vals[2] = constrain((avgVal - 128) * 4, 0, 255);
  vals[3] = constrain((avgVal - 192) * 4, 0, 255);
  
  for(int i = 0; i < 4; i++) {
    pixels.setPixelColor(i, pixels.Color(vals[i] * (r / 255.0), vals[i] * (g / 255.0), vals[i] * (b / 255.0)));
  }
  pixels.show();
  
  if(digitalRead(CHANGE_PIN) && !colorChanged) {
    randColors();
    colorChanged = 1;
  } else if (!digitalRead(CHANGE_PIN)) {
    colorChanged = 0;
  }
  delay(25);
}

