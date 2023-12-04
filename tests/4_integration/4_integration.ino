// test 4:
// read LDR sensor & detect when the light is turned off
// connect XIAO esp32s3 to WiFi & send webhook to IFTTT when the light is turned off

////////////////
// Parameters //
////////////////

// LDR parameters
int LDRsensor = A0;
int sensorValue;
int threshold = 100;
bool light = false;
bool old_light = false;
bool send = false;

// WiFi parameters
#include "WiFi.h"
#include "HTTPClient.h"
#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char password[] = SECRET_PASS;
char hostname[] = "ESP23S_LDR";

//  IFTTT parameters
const String event = IFTTT_EVENT_NAME;
const String key = IFTTT_API_KEY;
const String HOST_NAME = "https://maker.ifttt.com";
const String PATH_NAME = "/trigger/" + event + "/json/with/key/" + key;
const String queryString = "variable1=1";

///////////////////////////////
// Function: connect to WiFI //
///////////////////////////////

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

//////////////////////////////////
// Function: send IFTTT webhook //
//////////////////////////////////

void sendWebhook() {
  // send webhook
  HTTPClient http;
  http.begin(HOST_NAME + PATH_NAME);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(queryString);

  // error handling
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  // close connection
  http.end();
}

////////////////////////////
// Arduino Main Functions //
////////////////////////////

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // set WiFi to station mode
  WiFi.mode(WIFI_STA);
  // disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(100);
  // attempt to connect to Wifi network:
  initWiFi();
}

void loop() {
  // read LDR value
  sensorValue = analogRead(LDRsensor);
  Serial.println(sensorValue);

  // test if light is turned off
  if (sensorValue > threshold) {
    light = true;
  } else {
    light = false;
  }
  if (light != old_light) {
    old_light = light;
    if (!light) {
      Serial.println("Light turned off");
      send = true;
    }
  }

  // send a webhook to IFTTT if the light is turned off
  if (send) {
    Serial.println("Sending message to IFTTT ...");
    // blink to indicate IFTTT message is being sent
    for (int i = 0; i < 10; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
    // connect to WiFi if not connected
    if (WiFi.status() != WL_CONNECTED) {
      initWiFi();
    }
    // send webhook
    sendWebhook();
    // reset send flag
    send = false;
  }

  // set general sample rate (~ power consumption)
  delay(1000);
}