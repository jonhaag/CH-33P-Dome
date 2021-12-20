#include <Adafruit_NeoPixel.h>

//define NeoPixel Pin and Number of LEDs
#define EYE1 2
#define NUM_LEDS 2

#define EYE2 3

#define REAR_PIN 4
#define MATRIX_LEDS 64

#define RIPPLE_BRIGHTNESS 200
#define RIPPLE_DELAY 5

//create NeoPixel strips
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, EYE1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, EYE2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel matrix = Adafruit_NeoPixel(MATRIX_LEDS, REAR_PIN, NEO_GRB + NEO_KHZ800);

//global LED array
int ledArray[NUM_LEDS][2];

void setup() {
  // start the strip and blank it out
  strip1.begin();
  strip1.show();

  strip2.begin();
  strip2.show();

  matrix.begin();
  matrix.show();

  //seed RND generator
  randomSeed(analogRead(0)); 

  //populate the LED array with RND values and light it up
  for (int i = 0; i <= NUM_LEDS - 1; i++) {
    ledArray[i][0] = random(0,RIPPLE_BRIGHTNESS);
    strip1.setPixelColor(i,ledArray[i][0],0,0);
    strip2.setPixelColor(i,ledArray[i][0],0,0);
    ledArray[i][1] = random(0,2);
  }

  strip1.show();
  strip2.show();

  //populate the rear LED matrix with green and purple values and light it up
  for (int i = 0; i <= (MATRIX_LEDS)-41; i++) {
    matrix.setPixelColor(i, matrix.Color(150, 0, 120));
  }

  matrix.show();
}

void loop() {
  ripple();
}

void ripple() {
  for (int i = 0; i <= NUM_LEDS - 1; i++) {
    if (ledArray[i][1] == 0) {
      //fade down
      ledArray[i][0]--;
    }
    else {
      //fade up
      ledArray[i][0]++;
    }

    if (ledArray[i][0] <= -RIPPLE_BRIGHTNESS) {
      ledArray[i][1] = 1;
    }

    if (ledArray[i][0] >= RIPPLE_BRIGHTNESS) {
      ledArray[i][1] = 0;
    }

    int brightness = ledArray[i][0];
    if (brightness < 0) {
      brightness = 0;
    }
    strip1.setPixelColor(i, brightness, 255, 255);
    strip2.setPixelColor(i, brightness, 255, 255);
  }
  strip1.show();
  strip2.show();
  delay(RIPPLE_DELAY);
}
