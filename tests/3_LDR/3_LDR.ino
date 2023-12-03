// test 3: read LDR sensor & detect when the light is turned off

int LDRsensor = A0;
int threshold = 100;
bool light = false;
bool old_light = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor
  int sensorValue = analogRead(LDRsensor);
  Serial.println(sensorValue);

  // check if the light is on or off
  if (sensorValue > threshold) {
    light = true;
    // Serial.println("Light: on");
  } else {
    light = false;
    // Serial.println("Light: off");
  }

  // check if the light status has changed
  if (light != old_light) {
    // Serial.println("The reading has changed!");
    old_light = light;
    if (!light) {
      Serial.println("Flush it");
    }
  }

  delay(1000);
}