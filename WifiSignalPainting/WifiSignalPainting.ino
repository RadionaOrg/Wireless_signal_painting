/*
   ESP8266 WiFi light painting stick
*/
#include <ESP8266WiFi.h>

//Enter your wifi data below
const char* myssid = "Your wifi SSID";
const char* mypass = "Your wifi password";

//We will store signal data in this varible
long rssi;

void setup() {
  //Starting serial for debuging purpose
  Serial.begin(115200);

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
  Serial.println(map(rssi, -100, 0, 0, 90));
  //Wait for 1sec
  delay(1000);
}
