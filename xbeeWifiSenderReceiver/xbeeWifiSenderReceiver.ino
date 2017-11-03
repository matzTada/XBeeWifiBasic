#include "xbwifi.h"

int count = 0;
unsigned long pastMillis = millis();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  String hoge = wifireceive(Serial1);
  if (hoge.length() > 0) Serial.println(hoge);

  int destaddr [] = {10, 24, 12, 130};
  int destport = 9750;
  int srcport = 9750;
  String data = "Hello," + String(count) + "times," + String(millis() - pastMillis) + "ms\n";
  pastMillis = millis();
  count++;
  wifisend(Serial1, destaddr, destport, srcport, data);

  //  delay(100);
}

