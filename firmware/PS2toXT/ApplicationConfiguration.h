#ifndef _APPLICATIONCONFIGURATION_h
#define _APPLICATIONCONFIGURATION_h

#pragma region Definitions

/**
 * @brief If uncomment then no XT data will be send through the interface.
 * 
 */
#define DUMMY_SEND

/**
 * @brief Send data via serial port what is going on.
 * 
 */
#define DEBUG

/**
 * @brief XT byte size.
 * 
 */
#define XT_BYTE_SIZE 8

/**
 * @brief Trans code table size.
 * 
 */
#define TRANS_CODE_TABLE_SIZE 256

/**
 * @brief PS CLOCK DATA
 * 
 */
#define PIN_PS_CLK 2

/**
 * @brief PS DATA PIN
 * 
 */
#define PIN_PS_DATA 4

/**
 * @brief XT CLOCK PIN
 * 
 */
#define PIN_XT_CLK 3

/**
 * @brief XT DATA PIN
 * 
 */
#define PIN_XT_DATA 5



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
