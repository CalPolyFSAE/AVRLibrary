/*
 * CPFEAVRAnalog.cpp


 *
 *  Created on: Jun 1, 2015
 *      Author: thomaswillson
 */

#include "arduino/Arduino.h"
#include "CPFEAVRAnalog.h"

CPFEAVRAnalog* CPFEAVRAnalog::currentConversion;

ISR(ADC_vect) {
   CPFEAVRAnalog::adcInterruptHandler();
}

