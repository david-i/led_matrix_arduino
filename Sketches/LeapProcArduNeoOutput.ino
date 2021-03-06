
#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 3, NEO_RGB + NEO_KHZ800);

int previousPosition;
int currentPosition;
int serialInput;

void setup() {
  strip.begin();
  strip.setBrightness(100); 
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600); // Listen for input
}

void loop() {
  if (Serial.available()) {
    serialInput = Serial.read();   
    // if our position has changed
    if(serialInput != currentPosition) {  
      // take note of where we were    
      previousPosition = currentPosition;  
      // take note of where we are now 
      currentPosition = serialInput;  
      
      // make the current LED a pretty rainbow colour
      strip.setPixelColor(currentPosition, 255); 
      strip.show();
      
      // make the previous LED turn off
      strip.setPixelColor(previousPosition, rainbow);
      strip.show();
    }
  }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
     return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
     WheelPos -= 85;
     return strip.Color(255 - WheelPos, 0, WheelPos);
  } else {
     WheelPos -= 170;
     return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

