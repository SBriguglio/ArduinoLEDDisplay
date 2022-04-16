#include <FastLED.h>

#define LED_PIN     6
#define BRIGHTNESS  50
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND  20
#define BASE_SIZE   8
#define HEIGHT_SIZE 8
#define NUM_LEDS    BASE_SIZE * HEIGHT_SIZE

CRGB leds[NUM_LEDS];
int index = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));
}

void loop() {
  // reset matrix
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // select random square size
  int sqr_size = 6;
  paintSquare(index++, sqr_size);
  if(index >= NUM_LEDS) index = 0;

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void paintBug(int i){
  // this square red
  leds[i++] =   CRGB::Red;

  // next square blue
  if(i == NUM_LEDS){
    leds[0] = CRGB::Blue;
    i = 0;
  }
  else leds[i] = CRGB::Blue;
}

void paintSquare(int i, int n){
  /*  Paints an nxn square onto the led matrix where 
   *  index i is the top right corner of the square.
   *  The top face is red, right face is blue, left
   *  face is green and bottom face is yellow.
   */

  // top face
  int t_i = i;
  paintRow(i, n, CRGB::Red);

  // bottom face
  if((floor(i/BASE_SIZE) - n + 1) >= 0){
    int i_b = down(i, n);
    if(i_b >= 0) paintRow(i_b, n, CRGB::Yellow);
  }
  // right face
  int r_i = i;
  paintColumn(r_i, n, CRGB::Blue);
  
  // left face
  if((r_i/BASE_SIZE)%2 == 0){
    // even row 
    int L = floor(i / BASE_SIZE) * BASE_SIZE;
    int l_i = i - n + 1;
    if(l_i >= L) paintColumn(l_i, n, CRGB::Green);
  }
  else{
    // odd row
    int R = floor(i / BASE_SIZE) * BASE_SIZE;
    int L = R + BASE_SIZE - 1;
    int l_i = i + n - 1;
    if(l_i <= L) paintColumn(l_i, n, CRGB::Green);
  }
  
}

void paintRow(int i, int n, CRGB colour){
  /* Paints a row in the array (i-n, i] the colour.
   * This ALWAYS paints to the LEFT of i as it APPEARS
   * in the LED matrix. (note the ZigZag pattern) 
   */
  int j = i;
  if((i/BASE_SIZE)%2 == 0){
    // even row
    int L = floor(i / BASE_SIZE) * BASE_SIZE;
    int R = L + BASE_SIZE - 1;

    while((j >= L) && (j > i-n)){
      leds[j--] = colour;
    }
  }
  else{
    // odd row
    int R = floor(i / BASE_SIZE) * BASE_SIZE;
    int L = R + BASE_SIZE - 1;

    while((j <= L) && (j < i+n)){
      leds[j++] = colour;
    }
  }
}

void paintColumn(int i, int n, CRGB colour){
  /*  Paints the column of n pixels including i below i.
   */
  if(n > 0 && i > 0){
    int row = i / BASE_SIZE;
    int delta = i - (row * BASE_SIZE);
    int next_i = (row * BASE_SIZE) - delta - 1;
    leds[i] = colour;
    paintColumn(next_i, n-1, colour);
  }
}

int down(int i, int n){
  /*  Returns the pixel index of the pixel n pixels 
   *  below i.
   */
  if(n == 1) return i;

  int row = i / BASE_SIZE;
  int delta = i - (row * BASE_SIZE);
  int next_i = (row * BASE_SIZE) - delta - 1;
  return down(next_i, n-1);
}


