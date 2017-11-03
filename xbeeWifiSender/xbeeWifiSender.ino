#include "xbwifi.h"

int count = 0;
unsigned long pastMillis = millis();

void setup() {
  Serial.begin(115200);
}

void loop() {
  int destaddr [] = {10, 24, 12, 130};
  int destport = 9750;
  int srcport = 9750;
  String data = "Hello," + String(count) + "times," + String(millis() - pastMillis) + "ms\n";
  pastMillis = millis();
  count++;

  wifisend(Serial, destaddr, destport, srcport, data);

  //  delay(100);
}




