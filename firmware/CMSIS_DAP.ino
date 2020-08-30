/*
  CMSIS_DAP

  Modified form ljbfly's implementation, working but a lot to improve
  RST   -> P30
  SWCLK -> P31
  SWDIO -> P32
  These pins works in OC mode with pull-up resistor (70K). Should be safe to connect 3.3V part.

  created 2020
  by Deqing Sun for use with CH55xduino

  This example code is in the public domain.

*/


#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "src/CMSIS_DAPusb/DAP.h"


extern volatile __xdata uint8_t USBByteCountEP1;


void setup() {
  USBInit();
}

void loop() {
  if (USBByteCountEP1) {
    DAP_Thread();
    USBByteCountEP1 = 0 ;

    UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_R_RES | UEP_R_RES_ACK; //enable receive

    UEP1_T_LEN = 64;
    UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK; //enable send
  }
}
