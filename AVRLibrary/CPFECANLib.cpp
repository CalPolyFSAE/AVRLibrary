/*
 * CPFECANLib.cpp
 *
 *  Created on: May 21, 2015
 *      Author: thomaswillson
 */

#include <stdio.h>
#include "arduino/Arduino.h"
#include "CPFECANLib.h"

ISR(CANIT_vect,ISR_BLOCK) {
   uint8_t origCANPAGE = CANPAGE;
   while (CANSIT2 | CANSIT1) {

      if (CANSIT2 & BIT0) CANPAGE = 0x00;
      else if (CANSIT2 & BIT1) CANPAGE = 0x10;
      else if (CANSIT2 & BIT2) CANPAGE = 0x20;
      else if (CANSIT2 & BIT3) CANPAGE = 0x30;
      else if (CANSIT2 & BIT4) CANPAGE = 0x40;
      else if (CANSIT2 & BIT5) CANPAGE = 0x50;
      else if (CANSIT2 & BIT6) CANPAGE = 0x60;
      else if (CANSIT2 & BIT7) CANPAGE = 0x70;
      else if (CANSIT1 & BIT0) CANPAGE = 0x80;
      else if (CANSIT1 & BIT1) CANPAGE = 0x90;
      else if (CANSIT1 & BIT2) CANPAGE = 0xA0;
      else if (CANSIT1 & BIT3) CANPAGE = 0xB0;
      else if (CANSIT1 & BIT4) CANPAGE = 0xC0;
      else if (CANSIT1 & BIT5) CANPAGE = 0xD0;
      else if (CANSIT1 & BIT6) CANPAGE = 0xE0;

      if (CANSTMOB & (1 << RXOK)) {
         CANSTMOB = 0x00;
         CPFECANLib::rxInt();
      }
   }
   CANPAGE = origCANPAGE;
}

CPFECANLib::CAN_MSG_RX CPFECANLib::rxIntFunc;

