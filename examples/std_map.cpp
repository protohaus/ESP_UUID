#include <map>

#include "esp_uuid.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  std::map<esp_uuid::UUID, String> dict;

  esp_uuid::UUID uuid_a;
  dict.emplace(uuid_a, String("Hello"));
  esp_uuid::UUID uuid_b;
  dict.emplace(uuid_b, String(" there!"));
  
  const auto text_a = dict.find(uuid_a);
  if (text_a != dict.end()) {
    Serial.print(text_a->second);
  }
  const auto text_b = dict.find(uuid_b);
  if (text_b != dict.end()) {
    Serial.println(text_b->second);
  }
  const auto text_c = dict.find(esp_uuid::UUID());
  if (text_c != dict.end()) {
    Serial.print(text_c->second);
  } else {
    Serial.println("Not found");
  }
  Serial.printf("\n\n");
  delay(5000);
}