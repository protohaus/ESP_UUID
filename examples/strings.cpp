#include "esp_uuid.h"

const char* uuid_a = "0B3E66C5-9072-440F-A5C1-75139AC4E2F0";
String uuid_b = "9F51C7D8-0D0E-4834-9A8A-0F4CE5BAB9E7";
String invalid_uuid = "9F51C7D80D0E48349A8A0F4CE5BAB9E7";

void setup() {
  Serial.begin(115200);
}

void loop() {
  esp_uuid::UUID uuid = esp_uuid::UUID(uuid_a);
  Serial.println(uuid);
  Serial.printf("Is uuid_a valid: %d\n", uuid.isValid());

  uuid = esp_uuid::UUID(uuid_b);
  Serial.println(uuid);
  Serial.printf("Is uuid_b valid: %d\n", uuid.isValid());

  uuid = esp_uuid::UUID(invalid_uuid);
  Serial.println(uuid);
  Serial.printf("Is invalid_uuid valid: %d\n\n\n", uuid.isValid());

  delay(5000);
}