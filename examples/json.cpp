#include <Wire.h>

#include "esp_uuid.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  DynamicJsonDocument doc(1024);
  doc["id"] = "0B3E66C5-9072-440F-A5C1-75139AC4E2F0";
  doc["bad_id"] = "00000000-0000-0000-0000-000000000000";
  serializeJson(doc, Serial);
  Serial.printf("\n\n");

  JsonVariantConst json_uuid = doc["id"];
  esp_uuid::UUID uuid = esp_uuid::UUID(json_uuid);
  Serial.println(uuid);
  Serial.printf("Is id valid: %d\n", uuid.isValid());

  json_uuid = doc["bad_id"];
  uuid = esp_uuid::UUID(json_uuid);
  Serial.println(uuid);
  Serial.printf("Is bad_id valid: %d\n\n\n", uuid.isValid());

  delay(5000);
}