#include "esp_uuid.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  esp_uuid::UUID uuid = esp_uuid::UUID();
  Serial.println(uuid);
}