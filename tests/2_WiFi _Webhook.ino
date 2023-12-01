// test 2: connect XIAO esp32s3 to WiFi & send webhook

// load libraries for WiFi & Webhook 
#include "WiFi.h"
#include <IFTTTWebhook.h>

// set Wifi credentials
// passwords are stored in a seperate "arduino_secrets.h" file
#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char password[] = SECRET_PASS;

// set IFTTT webhook credentials
char api_key[] = IFTTT_API_KEY;
char ifttt_event[] = IFTTT_EVENT_NAME;

// create a WiFi connection function
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);

   // set WiFi to station mode
  WiFi.mode(WIFI_STA);

  // disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  initWiFi();

  // define IFTTT webhook
  Serial.println("Connecting to IFTTT");
  IFTTTWeb webhook(api_key, ifttt_event);
  Serial.println("Webhook initialized");
}

void loop() {
  webhook.trigger("flush");
  delay(10000);
}