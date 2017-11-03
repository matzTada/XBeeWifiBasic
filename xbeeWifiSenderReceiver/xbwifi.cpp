#include "xbwifi.h"

void sendByte(Stream &serial, uint8_t b, bool escape) {
  if (escape && (b == START_BYTE || b == ESCAPE || b == XON || b == XOFF)) {
    serial.write(ESCAPE);
    serial.write(b ^ 0x20);
    //    serial.print(String(ESCAPE, HEX));
    //    serial.print(" ");
    //    serial.print(String(b ^ 0x20, HEX));
    //    serial.print(" ");
  } else {
    serial.write(b);
    //    serial.print(String(b, HEX));
    //    serial.print(" ");
  }
}


void wifisend(Stream &serial, int destaddr[], int destport, int srcport, String data) {
  // start delimiter
  sendByte(serial, START_BYTE, false);

  // send length
  uint8_t msbLen = ((TX_IPv4_LEN + data.length()) >> 8) & 0xff;
  uint8_t lsbLen = (TX_IPv4_LEN + data.length()) & 0xff;
  sendByte(serial, msbLen, true);
  sendByte(serial, lsbLen, true);

  //check sum
  uint8_t checksum = 0;

  // Frame type
  sendByte(serial, TX_IPv4, true);
  checksum += TX_IPv4;

  // Frame ID
  sendByte(serial, 0, true);
  checksum += 0;

  // IPv4 dest addr
  for (int i = 0; i < 4; i++) {
    sendByte(serial, (uint8_t)destaddr[i], true);
    checksum += (uint8_t)destaddr[i];
  }

  // dest port
  uint8_t msbDP = (destport >> 8) & 0xff;
  uint8_t lsbDP = destport & 0xff;
  sendByte(serial, msbDP, true);
  sendByte(serial, lsbDP, true);
  checksum += msbDP;
  checksum += lsbDP;

  // src port
  uint8_t msbSP = (srcport >> 8) & 0xff;
  uint8_t lsbSP = srcport & 0xff;
  sendByte(serial, msbSP, true);
  sendByte(serial, lsbSP, true);
  checksum += msbSP;
  checksum += lsbSP;

  // Protocol
  sendByte(serial, 0, true);
  checksum += 0;

  // Transmit options
  sendByte(serial, 0, true);
  checksum += 0;

  //RF data
  for (int i = 0; i < data.length(); i++) {
    sendByte(serial, (uint8_t)data.charAt(i), true);
    checksum += (uint8_t)data.charAt(i);
  }

  // perform 2s complement
  checksum = 0xff - checksum;
  sendByte(serial, checksum, true);

  // send packet (Note: prior to Arduino 1.0 this flushed the incoming buffer, which of course was not so great)
  serial.flush();
}
