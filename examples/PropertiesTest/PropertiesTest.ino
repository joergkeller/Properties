#include <SD.h>
#include "Properties.h"

#define CARD_CS_PIN        5     // Card chip select pin

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Start example");

  if (!SD.begin(CARD_CS_PIN)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD initialized");

  File file = SD.open("settings.cfg");
  Properties cfg = Properties(file);
  String key = "volume.initial";
  String val = cfg.readString(key);
  Serial.print("Initial volume: "); Serial.println(val.toInt());
  file.close();
}

void loop() {
  // nop
}
