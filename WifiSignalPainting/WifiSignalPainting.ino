/*
   ESP8266 WiFi light painting stick
   For Strip you will need
   http://fastled.io library from
   https://github.com/FastLED/FastLED
*/

#include "FastLED.h"
#include <ESP8266WiFi.h>

// Define pin on ESP that will be connected to strip
#define DATA_PIN 1

// Define no of leds you have on strip
#define NUM_LEDS 10

// Define the array of leds
CRGB leds[NUM_LEDS];

// Enter your wifi data below
const char* myssid = "Your wifi SSID";
const char* mypass = "Your wifi password";

// We will store signal data in this varible
long rssi;
int signalStrenght;

void setup() {
  //Starting serial for debuging purpose
  Serial.begin(115200);

  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);

  Serial.println("\nESP8266 WiFi light painting stick");

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  //Initiate connection
  WiFi.begin(myssid, mypass);
  Serial.print("Connecting");

  // Wait for successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nConnected to: ");
  Serial.println(myssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

void loop() {
  //Get signal strenght
  rssi = WiFi.RSSI();  // eg. -63
  //Print signal strenght (not mapped)
  Serial.println(rssi);
  //Print signal strenght mapped from 0-90 for easier usage
  signalStrenght = int(map(rssi, -100, -50, 1, NUM_LEDS));
    int colorSegments = NUM_LEDS / 5 ;
  Serial.println(signalStrenght);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    int setColors = i / colorSegments ;
    if (setColors < 1)
    {
      if (signalStrenght >= i)
        leds[i] = CRGB::Red;
      else
        leds[i] = CRGB::Black;
    }
    else if  (setColors >= 1 && setColors < 2)
    {
      if (signalStrenght >= i)
        leds[i] = CRGB::GreenYellow;
      else
        leds[i] = CRGB::Black;
    }
    else if  (setColors >= 2 && setColors < 3)
    {
      if (signalStrenght >= i)
        leds[i] = CRGB::Orange;
      else
        leds[i] = CRGB::Black;
    }
    else if  (setColors >= 3 && setColors < 4)
    {
      if (signalStrenght >= i)
        leds[i] = CRGB::Blue;
      else
        leds[i] = CRGB::Black;
    }
    else if  (setColors >= 4)
    {
      if (signalStrenght >= i)
        leds[i] = CRGB::Green;
      else
        leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}
