// test 2: connect XIAO esp32s3 to WiFi & send webhook
// this scripts sends a webhook to IFTTT every 10 seconds

// Load WiFi libraries
#include "WiFi.h"
#include "HTTPClient.h"

// Set passwords for WiFi
#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char password[] = SECRET_PASS;
char hostname[] = "ESP23S_lightsensor";

// Set IFTTT credentials (get event & API key from "arduino_secrets.h")
const String event = IFTTT_EVENT_NAME;
const String key = IFTTT_API_KEY;
const String HOST_NAME = "https://maker.ifttt.com";
const String PATH_NAME = "/trigger/" + event + "/json/with/key/" + key;
const String queryString = "variable1=1";

// create a function to set-up the WiFi connection
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  WiFi.hostname(hostname);
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
}

void loop() {
  // define the http client
  HTTPClient http;

  // open http connection
  http.begin(HOST_NAME + PATH_NAME);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // post the http payload
  int httpCode = http.POST(queryString);

  // error handling (httpCode is negative on error)
  if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

  delay(10000);
}