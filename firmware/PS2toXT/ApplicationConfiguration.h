#ifndef _APPLICATIONCONFIGURATION_h
#define _APPLICATIONCONFIGURATION_h

#pragma region Definitions

#define DEBUG

#define PIN_PS_CLK 2 // PS CLOCK DATA
#define PIN_PS_DATA 4 // PS DATA PIN

#define PIN_XT_CLK 3 // XT CLOCK PIN
#define PIN_XT_DATA 5 // XT DATA PIN

#pragma endregion

#pragma region Headers

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma endregion

#pragma region Enums

#pragma endregion

#endif
