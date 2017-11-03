//ref xbee arduino library
// xbee wifi must be set to API=2 (API mode with escape

#ifndef XBWIFI_H
#define XBWIFI_H

#include <Arduino.h>

#define START_BYTE 0x7e
#define ESCAPE 0x7d
#define XON 0x11
#define XOFF 0x13

#define TX_IPv4_LEN 12
#define TX_IPv4 0x20

void sendByte(Stream &serial, uint8_t b, bool escape);
void wifisend(Stream &serial, int destaddr[], int destport, int srcport, String data);

#endif

