
#pragma region Headers

#include "ApplicationConfiguration.h"

#include <PS2KeyAdvanced.h>

#pragma endregion

#pragma region Variables

/**
 * @brief PS2 key hit.
 * 
 */
uint16_t PS2Key_g;

/**
 * @brief PS2 keyboard.
 * 
 */
PS2KeyAdvanced PS2Keyboard_g;

/**
 * @brief Trans code table.
 * 
 */
unsigned char TransCodeTable_g[TRANS_CODE_TABLE_SIZE];

/**
 * @brief Trans coded key.
 * 
 */
unsigned char TransCoded_g;

#pragma endregion

#pragma region Prototypes

/**
 * @brief Set the up trans table map.
 * 
 */
void setup_trans_table();

/**
 * @brief Set the up XT keyboard object.
 * 
 */
void setup_xt_kbd();

/**
 * @brief Send key via XT keyboard interface.
 * 
 * @param value 
 */
void send_xt_kbd(unsigned char value);

#pragma endregion

/**
 * @brief Setup
 * 
 */
void setup()
{
#ifdef DEBUG
    Serial.begin(DEBUG_BAUD);
#endif

    setup_trans_table();
    
    PS2Keyboard_g.begin(PIN_PS_DATA, PIN_PS_CLK);

    setup_xt_kbd();
}

/**
 * @brief Loop
 * 
 */
void loop()
{
    if (PS2Keyboard_g.available())
    {
        PS2Key_g = PS2Keyboard_g.read();
        
#ifdef DEBUG
        if (PS2Key_g > 0)
        {
            Serial.print(F("Value "));
            Serial.print(PS2Key_g, HEX);
            Serial.print(F(" - Status Bits "));
            Serial.print(PS2Key_g >> 8, HEX);
            Serial.print(F("  Code "));
            Serial.println(PS2Key_g & 0xFF, HEX);
        }
#endif
        
    if (!(PS2Key_g & PS2_BREAK))
    {
        switch (PS2Key_g & 0xff)
        {
        case PS2_KEY_L_CTRL:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x1D);
            break;
        case PS2_KEY_R_ALT:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x38);
            break;
        case PS2_KEY_INSERT:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x52);
            break;
        case PS2_KEY_HOME:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x47);
            break;
        case PS2_KEY_END:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x4F);
            break;
        case PS2_KEY_DN_ARROW:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x50);
            break;
        case PS2_KEY_PGDN:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x51);
            break;
        case PS2_KEY_L_ARROW:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x4B);
            break;
        case PS2_KEY_R_ARROW:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x4D);
            break;
        case PS2_KEY_UP_ARROW:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x48);
            break;
        case PS2_KEY_PGUP:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x49);
            break;
        case PS2_KEY_DELETE:
            send_xt_kbd(0xE0);
            send_xt_kbd(0x53);
            break;
        default:
            TransCoded_g = TransCodeTable_g[PS2Key_g & 0xff];
            send_xt_kbd(TransCoded_g);
            break;
        }
    }

    if ((PS2Key_g & PS2_BREAK))
    {
        switch (PS2Key_g & 0xff)
        {
            case PS2_KEY_L_CTRL:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x1D | 0x80);
                break;
            case PS2_KEY_R_ALT:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x38 | 0x80);
                break;
            case PS2_KEY_INSERT:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x52 | 0x80);
                break;
            case PS2_KEY_HOME:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x47 | 0x80);
                break;
            case PS2_KEY_END:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x4F | 0x80);
                break;
            case PS2_KEY_DN_ARROW:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x50 | 0x80);
                break;
            case PS2_KEY_PGDN:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x51 | 0x80);
                break;
            case PS2_KEY_L_ARROW:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x4B | 0x80);
                break;
            case PS2_KEY_R_ARROW:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x4D | 0x80);
                break;
            case PS2_KEY_UP_ARROW:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x48 | 0x80);
                break;
            case PS2_KEY_PGUP:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x49 | 0x80);
                break;
            case PS2_KEY_DELETE:
                send_xt_kbd(0xE0);
                send_xt_kbd(0x53 | 0x80);
                break;
            default: {
                TransCoded_g = TransCodeTable_g[PS2Key_g & 0xff];
                send_xt_kbd(TransCoded_g | 0x80);
                }
            }
        }
    }
    
    // power-on self test
    if (digitalRead(PIN_XT_CLK) == LOW)
    {
        delay(20);
        send_xt_kbd(0xAA);
    }
}

#pragma region Functions

/**
 * @brief Set the up trans table map.
 * 
 */
void setup_trans_table()
{
    for (int index = 0; index < TRANS_CODE_TABLE_SIZE; index++)
    {
        TransCodeTable_g[index] = 0xff;
    }

    TransCodeTable_g[PS2_KEY_SCROLL] = 0x46;
    TransCodeTable_g[PS2_KEY_CAPS] = 0x3A;
    TransCodeTable_g[PS2_KEY_PAUSE] = 0x5f;
    TransCodeTable_g[PS2_KEY_L_SHIFT] = 0x2A;
    TransCodeTable_g[PS2_KEY_R_SHIFT] = 0x36;
    TransCodeTable_g[PS2_KEY_L_ALT] = 0x38;
    TransCodeTable_g[PS2_KEY_L_CTRL] = 0x1D;
    TransCodeTable_g[PS2_KEY_L_ARROW] = 0x4B;
    TransCodeTable_g[PS2_KEY_R_ARROW] = 0x4D;
    TransCodeTable_g[PS2_KEY_UP_ARROW] = 0x48;
    TransCodeTable_g[PS2_KEY_DN_ARROW] = 0x50;
    TransCodeTable_g[PS2_KEY_DELETE] = 0x53;
    TransCodeTable_g[PS2_KEY_ESC] = 0x01;
    TransCodeTable_g[PS2_KEY_BS] = 0x0E;
    TransCodeTable_g[PS2_KEY_TAB] = 0x0F;
    TransCodeTable_g[PS2_KEY_ENTER] = 0x1C;
    TransCodeTable_g[PS2_KEY_SPACE] = 0x39;
    TransCodeTable_g[PS2_KEY_SEMI] = 0x27;
    TransCodeTable_g[PS2_KEY_KP0] = 0x52;
    TransCodeTable_g[PS2_KEY_KP1] = 0x4F;
    TransCodeTable_g[PS2_KEY_KP2] = 0x50;
    TransCodeTable_g[PS2_KEY_KP3] = 0x51;
    TransCodeTable_g[PS2_KEY_KP4] = 0x4B;
    TransCodeTable_g[PS2_KEY_KP5] = 0x4C;
    TransCodeTable_g[PS2_KEY_KP6] = 0x4D;
    TransCodeTable_g[PS2_KEY_KP7] = 0x47;
    TransCodeTable_g[PS2_KEY_KP8] = 0x48;
    TransCodeTable_g[PS2_KEY_KP9] = 0x49;
    TransCodeTable_g[PS2_KEY_OPEN_SQ] = 0x1A;
    TransCodeTable_g[PS2_KEY_CLOSE_SQ] = 0x1B;
    TransCodeTable_g[PS2_LOCK_NUM] = 0x45;
    //TransCodeTable_g[PS2_KEY_KP_DOT]=0x53;
    TransCodeTable_g[PS2_KEY_KP_PLUS] = 0x4E;
    TransCodeTable_g[PS2_KEY_KP_MINUS] = 0x4A;
    TransCodeTable_g[PS2_KEY_KP_TIMES] = 0x37;
    TransCodeTable_g[PS2_KEY_KP_DIV] = 0x35;
    TransCodeTable_g[PS2_KEY_KP_ENTER] = 0x01;
    TransCodeTable_g[PS2_KEY_0] = 0x0B;
    TransCodeTable_g[PS2_KEY_1] = 0x02;
    TransCodeTable_g[PS2_KEY_2] = 0x03;
    TransCodeTable_g[PS2_KEY_3] = 0x04;
    TransCodeTable_g[PS2_KEY_4] = 0x05;
    TransCodeTable_g[PS2_KEY_5] = 0x06;
    TransCodeTable_g[PS2_KEY_6] = 0x07;
    TransCodeTable_g[PS2_KEY_7] = 0x08;
    TransCodeTable_g[PS2_KEY_8] = 0x09;
    TransCodeTable_g[PS2_KEY_9] = 0x0A;
    TransCodeTable_g[PS2_KEY_APOS] = 0x28;
    TransCodeTable_g[PS2_KEY_COMMA] = 0x33;
    TransCodeTable_g[PS2_KEY_MINUS] = 0x0C;
    TransCodeTable_g[PS2_KEY_SCROLL] = 0x46;
    TransCodeTable_g[PS2_KEY_DOT] = 0x34;
    TransCodeTable_g[PS2_KEY_BACK] = 0x2B;
    TransCodeTable_g[PS2_KEY_SINGLE] = 0x29;
    TransCodeTable_g[PS2_KEY_DIV] = 0x35;
    TransCodeTable_g[PS2_KEY_SINGLE] = 28;
    TransCodeTable_g[PS2_KEY_A] = 0x1E;
    TransCodeTable_g[PS2_KEY_B] = 0x30;
    TransCodeTable_g[PS2_KEY_C] = 0x2E;
    TransCodeTable_g[PS2_KEY_D] = 0x20;
    TransCodeTable_g[PS2_KEY_E] = 0x12;
    TransCodeTable_g[PS2_KEY_F] = 0x21;
    TransCodeTable_g[PS2_KEY_G] = 0x22;
    TransCodeTable_g[PS2_KEY_H] = 0x23;
    TransCodeTable_g[PS2_KEY_I] = 0x17;
    TransCodeTable_g[PS2_KEY_J] = 0x24;
    TransCodeTable_g[PS2_KEY_K] = 0x25;
    TransCodeTable_g[PS2_KEY_L] = 0x26;
    TransCodeTable_g[PS2_KEY_M] = 0x32;
    TransCodeTable_g[PS2_KEY_N] = 0x31;
    TransCodeTable_g[PS2_KEY_O] = 0x18;
    TransCodeTable_g[PS2_KEY_P] = 0x19;
    TransCodeTable_g[PS2_KEY_Q] = 0x10;
    TransCodeTable_g[PS2_KEY_R] = 0x13;
    TransCodeTable_g[PS2_KEY_S] = 0x1F;
    TransCodeTable_g[PS2_KEY_T] = 0x14;
    TransCodeTable_g[PS2_KEY_U] = 0x16;
    TransCodeTable_g[PS2_KEY_V] = 0x2F;
    TransCodeTable_g[PS2_KEY_W] = 0x11;
    TransCodeTable_g[PS2_KEY_X] = 0x2D;
    TransCodeTable_g[PS2_KEY_Y] = 0x15;
    TransCodeTable_g[PS2_KEY_Z] = 0x2c;
    TransCodeTable_g[PS2_KEY_EQUAL] = 0x0D;
    TransCodeTable_g[PS2_KEY_F1] = 0x3B;
    TransCodeTable_g[PS2_KEY_F2] = 0x3C;
    TransCodeTable_g[PS2_KEY_F3] = 0x3D;
    TransCodeTable_g[PS2_KEY_F4] = 0x3E;
    TransCodeTable_g[PS2_KEY_F5] = 0x3F;
    TransCodeTable_g[PS2_KEY_F6] = 0x40;
    TransCodeTable_g[PS2_KEY_F7] = 0x41;
    TransCodeTable_g[PS2_KEY_F8] = 0x42;
    TransCodeTable_g[PS2_KEY_F9] = 0x43;
    TransCodeTable_g[PS2_KEY_F10] = 0x44;
    TransCodeTable_g[PS2_KEY_F11] = 0x85;
    TransCodeTable_g[PS2_KEY_F12] = 0x86;
}

/**
 * @brief Set the up XT keyboard object.
 * 
 */
void setup_xt_kbd()
{
    pinMode(PIN_XT_CLK, OUTPUT);
    pinMode(PIN_XT_DATA, OUTPUT);
    digitalWrite(PIN_XT_CLK, HIGH);
    digitalWrite(PIN_XT_DATA, HIGH);
}

/**
 * @brief Send key via XT keyboard interface.
 * 
 * @param value 
 */
void send_xt_kbd(unsigned char value)
{

#ifdef NO_SEND
    return;
#endif

    // 
    unsigned char BitsL[XT_BYTE_SIZE];

    byte PointerL = 0;

    // Wait sync front.
    while (digitalRead(PIN_XT_CLK) != HIGH);
    
    for (byte index = 0; index < XT_BYTE_SIZE; index++)
    {
        if (value & 1)
        {
            BitsL[index] = HIGH;
        }
        else
        {
            BitsL[index] = LOW;
        }

        value = value >> 1;
    }
    
    digitalWrite(PIN_XT_CLK, LOW);
    digitalWrite(PIN_XT_DATA, HIGH);
    delayMicroseconds(120);
    digitalWrite(PIN_XT_CLK, HIGH);
    delayMicroseconds(66);
    digitalWrite(PIN_XT_CLK, LOW);
    delayMicroseconds(30);
    digitalWrite(PIN_XT_CLK, HIGH);
        
    for (byte index = 0; index < XT_BYTE_SIZE; index++)
    {
        digitalWrite(PIN_XT_CLK, HIGH);
        digitalWrite(PIN_XT_DATA, BitsL[PointerL]);
        delayMicroseconds(95);
        digitalWrite(PIN_XT_CLK, LOW);
        digitalWrite(PIN_XT_DATA, LOW);
        PointerL++;
    }
    
    digitalWrite(PIN_XT_CLK, HIGH);
    digitalWrite(PIN_XT_DATA, LOW);
    delay(1);
}

#pragma endregion
