/**
 * @file SSD1309.h
 * @author Yunoshin Tani (taniyunoshin@gmail.com)
 * @brief SSD1309 OLED display driver
 * @details This is a library for the SSD1309 OLED display driver.
 * @version 1.0.0
 * @date 2025/02/27
 * @copyright Copyright (c) 2025
 */

#ifndef SSD1309_H
#define SSD1309_H

#include <mbed.h>

// 基本設定コマンド
#define SSD1309_SET_CONTRAST_CONTROL                 0x81    // コントラスト制御設定
#define SSD1309_ENTIRE_DISPLAY_ON                    0xA4    // 全画面表示ON（通常表示）
#define SSD1309_ENTIRE_DISPLAY_ON_IGNORE_RAM         0xA5    // 全画面表示ON（RAM無視）
#define SSD1309_SET_NORMAL_DISPLAY                   0xA6    // 通常表示モード
#define SSD1309_SET_INVERSE_DISPLAY                  0xA7    // 反転表示モード
#define SSD1309_SET_DISPLAY_OFF                      0xAE    // ディスプレイOFF
#define SSD1309_SET_DISPLAY_ON                       0xAF    // ディスプレイON

// アドレッシング設定コマンド
#define SSD1309_SET_LOWER_COLUMN                     0x00    // 下位カラムアドレス設定
#define SSD1309_SET_HIGHER_COLUMN                    0x10    // 上位カラムアドレス設定
#define SSD1309_SET_MEMORY_ADDRESSING_MODE           0x20    // メモリアドレッシングモード設定
#define SSD1309_SET_COLUMN_ADDRESS                   0x21    // カラムアドレス範囲設定
#define SSD1309_SET_PAGE_ADDRESS                     0x22    // ページアドレス範囲設定
#define SSD1309_SET_PAGE_START_ADDRESS               0xB0    // ページスタートアドレス設定

// ハードウェア設定コマンド
#define SSD1309_SET_DISPLAY_START_LINE               0x40    // ディスプレイスタートライン設定
#define SSD1309_SET_SEGMENT_REMAP                    0xA0    // セグメントリマップ設定
#define SSD1309_SET_MULTIPLEX_RATIO                  0xA8    // マルチプレックス比設定
#define SSD1309_SET_COM_OUTPUT_SCAN_DIR              0xC0    // COM出力スキャン方向設定
#define SSD1309_SET_DISPLAY_OFFSET                   0xD3    // ディスプレイオフセット設定
#define SSD1309_SET_COM_PINS                         0xDA    // COMピン構成設定

// クロック・電源設定コマンド
#define SSD1309_SET_DISPLAY_CLOCK_DIV                0xD5    // ディスプレイクロック分周比/振動数設定
#define SSD1309_SET_PRECHARGE_PERIOD                 0xD9    // プレチャージ期間設定
#define SSD1309_SET_VCOMH_DESELECT_LEVEL             0xDB    // VCOMHデセレクトレベル設定
#define SSD1309_NOP                                  0xE3    // NOP（No Operation）

// スクロール設定コマンド
#define SSD1309_RIGHT_HORIZONTAL_SCROLL              0x26    // 右方向水平スクロール設定
#define SSD1309_LEFT_HORIZONTAL_SCROLL               0x27    // 左方向水平スクロール設定
#define SSD1309_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29    // 垂直・右方向水平スクロール設定
#define SSD1309_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A    // 垂直・左方向水平スクロール設定
#define SSD1309_DEACTIVATE_SCROLL                    0x2E    // スクロール停止
#define SSD1309_ACTIVATE_SCROLL                      0x2F    // スクロール開始
#define SSD1309_SET_VERTICAL_SCROLL_AREA             0xA3    // 垂直スクロールエリア設定

#define DISPLAY_WIDTH 128
#define DISPLAY_HEGHT 64

class oled
{
public:
    oled(PinName sda, PinName scl, uint8_t address);

    bool command(uint8_t cmd);

    bool send(uint8_t data);

    void init();

    bool test();

    void clear();

    void fill();

    void setCursor(uint8_t x, uint8_t y);

    void drawPixel(uint8_t x, uint8_t y);

    void drawLine(uint8_t x = 255, uint8_t y = 255);

    void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

    void drawRect2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

    void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

    void fillRect2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

    void drawCircle(uint8_t x, uint8_t y, uint8_t r);

    void fillCircle(uint8_t x, uint8_t y, uint8_t r);

    void drawInt(int data, uint8_t x, uint8_t y, const char *option);

    void drawChar(char data);

    void drawText(const char *text, uint8_t x, uint8_t y);

    void drawQR(uint8_t x, uint8_t y);

    void drawQR(uint8_t data[25][8], uint8_t x, uint8_t y);

private:
    I2C _i2c;

    uint8_t _address;

    const uint8_t FONT5x8[95][5] = {
        {0x00, 0x00, 0x00, 0x00, 0x00},  // スペース ' '
        {0x00, 0x00, 0x5F, 0x00, 0x00},  // '!'
        {0x00, 0x07, 0x00, 0x07, 0x00},  // '"'
        {0x14, 0x7F, 0x14, 0x7F, 0x14},  // '#'
        {0x24, 0x2A, 0x7F, 0x2A, 0x12},  // '$'
        {0x23, 0x13, 0x08, 0x64, 0x62},  // '%'
        {0x36, 0x49, 0x55, 0x22, 0x50},  // '&'
        {0x00, 0x05, 0x03, 0x00, 0x00},  // '''
        {0x00, 0x1C, 0x22, 0x41, 0x00},  // '('
        {0x00, 0x41, 0x22, 0x1C, 0x00},  // ')'
        {0x14, 0x08, 0x3E, 0x08, 0x14},  // '*'
        {0x08, 0x08, 0x3E, 0x08, 0x08},  // '+'
        {0x00, 0x50, 0x30, 0x00, 0x00},  // ','
        {0x08, 0x08, 0x08, 0x08, 0x08},  // '-'
        {0x00, 0x60, 0x60, 0x00, 0x00},  // '.'
        {0x20, 0x10, 0x08, 0x04, 0x02},  // '/'
        {0x3E, 0x51, 0x49, 0x45, 0x3E},  // '0'
        {0x00, 0x42, 0x7F, 0x40, 0x00},  // '1'
        {0x42, 0x61, 0x51, 0x49, 0x46},  // '2'
        {0x21, 0x41, 0x45, 0x4B, 0x31},  // '3'
        {0x18, 0x14, 0x12, 0x7F, 0x10},  // '4'
        {0x27, 0x45, 0x45, 0x45, 0x39},  // '5'
        {0x3C, 0x4A, 0x49, 0x49, 0x30},  // '6'
        {0x01, 0x71, 0x09, 0x05, 0x03},  // '7'
        {0x36, 0x49, 0x49, 0x49, 0x36},  // '8'
        {0x06, 0x49, 0x49, 0x29, 0x1E},  // '9'
        {0x00, 0x36, 0x36, 0x00, 0x00},  // ':'
        {0x00, 0x56, 0x36, 0x00, 0x00},  // ';'
        {0x08, 0x14, 0x22, 0x41, 0x00},  // '<'
        {0x14, 0x14, 0x14, 0x14, 0x14},  // '='
        {0x00, 0x41, 0x22, 0x14, 0x08},  // '>'
        {0x02, 0x01, 0x51, 0x09, 0x06},  // '?'
        {0x32, 0x49, 0x79, 0x41, 0x3E},  // '@'
        {0x7E, 0x11, 0x11, 0x11, 0x7E},  // 'A'
        {0x7F, 0x49, 0x49, 0x49, 0x36},  // 'B'
        {0x3E, 0x41, 0x41, 0x41, 0x22},  // 'C'
        {0x7F, 0x41, 0x41, 0x22, 0x1C},  // 'D'
        {0x7F, 0x49, 0x49, 0x49, 0x41},  // 'E'
        {0x7F, 0x09, 0x09, 0x09, 0x01},  // 'F'
        {0x3E, 0x41, 0x49, 0x49, 0x7A},  // 'G'
        {0x7F, 0x08, 0x08, 0x08, 0x7F},  // 'H'
        {0x00, 0x41, 0x7F, 0x41, 0x00},  // 'I'
        {0x20, 0x40, 0x41, 0x3F, 0x01},  // 'J'
        {0x7F, 0x08, 0x14, 0x22, 0x41},  // 'K'
        {0x7F, 0x40, 0x40, 0x40, 0x40},  // 'L'
        {0x7F, 0x02, 0x0C, 0x02, 0x7F},  // 'M'
        {0x7F, 0x04, 0x08, 0x10, 0x7F},  // 'N'
        {0x3E, 0x41, 0x41, 0x41, 0x3E},  // 'O'
        {0x7F, 0x09, 0x09, 0x09, 0x06},  // 'P'
        {0x3E, 0x41, 0x51, 0x21, 0x5E},  // 'Q'
        {0x7F, 0x09, 0x19, 0x29, 0x46},  // 'R'
        {0x46, 0x49, 0x49, 0x49, 0x31},  // 'S'
        {0x01, 0x01, 0x7F, 0x01, 0x01},  // 'T'
        {0x3F, 0x40, 0x40, 0x40, 0x3F},  // 'U'
        {0x1F, 0x20, 0x40, 0x20, 0x1F},  // 'V'
        {0x3F, 0x40, 0x38, 0x40, 0x3F},  // 'W'
        {0x63, 0x14, 0x08, 0x14, 0x63},  // 'X'
        {0x03, 0x04, 0x78, 0x04, 0x03},  // 'Y'
        {0x61, 0x51, 0x49, 0x45, 0x43},  // 'Z'
        {0x00, 0x7F, 0x41, 0x41, 0x00},  // '['
        {0x02, 0x04, 0x08, 0x10, 0x20},  // '\'
        {0x00, 0x41, 0x41, 0x7F, 0x00},  // ']'
        {0x04, 0x02, 0x01, 0x02, 0x04},  // '^'
        {0x40, 0x40, 0x40, 0x40, 0x40},  // '_'
        {0x01, 0x02, 0x04, 0x00, 0x00},  // '`'
        {0x20, 0x54, 0x54, 0x54, 0x78},  // 'a'
        {0x7F, 0x48, 0x44, 0x44, 0x38},  // 'b'
        {0x38, 0x44, 0x44, 0x44, 0x20},  // 'c'
        {0x38, 0x44, 0x44, 0x48, 0x7F},  // 'd'
        {0x38, 0x54, 0x54, 0x54, 0x18},  // 'e'
        {0x08, 0x7E, 0x09, 0x01, 0x02},  // 'f'
        {0x08, 0x14, 0x54, 0x54, 0x3C},  // 'g'
        {0x7F, 0x08, 0x04, 0x04, 0x78},  // 'h'
        {0x00, 0x44, 0x7D, 0x40, 0x00},  // 'i'
        {0x20, 0x40, 0x44, 0x3D, 0x00},  // 'j'
        {0x7F, 0x10, 0x28, 0x44, 0x00},  // 'k'
        {0x00, 0x41, 0x7F, 0x40, 0x00},  // 'l'
        {0x7C, 0x04, 0x18, 0x04, 0x78},  // 'm'
        {0x7C, 0x08, 0x04, 0x04, 0x78},  // 'n'
        {0x38, 0x44, 0x44, 0x44, 0x38},  // 'o'
        {0x7C, 0x14, 0x14, 0x14, 0x08},  // 'p'
        {0x08, 0x14, 0x14, 0x18, 0x7C},  // 'q'
        {0x7C, 0x08, 0x04, 0x04, 0x08},  // 'r'
        {0x48, 0x54, 0x54, 0x54, 0x20},  // 's'
        {0x04, 0x3F, 0x44, 0x40, 0x20},  // 't'
        {0x3C, 0x40, 0x40, 0x20, 0x7C},  // 'u'
        {0x1C, 0x20, 0x40, 0x20, 0x1C},  // 'v'
        {0x3C, 0x40, 0x30, 0x40, 0x3C},  // 'w'
        {0x44, 0x28, 0x10, 0x28, 0x44},  // 'x'
        {0x0C, 0x50, 0x50, 0x50, 0x3C},  // 'y'
        {0x44, 0x64, 0x54, 0x4C, 0x44},  // 'z'
        {0x00, 0x08, 0x36, 0x41, 0x00},  // '{'
        {0x00, 0x00, 0x7F, 0x00, 0x00},  // '|'
        {0x00, 0x41, 0x36, 0x08, 0x00},  // '}'
    };

    const uint8_t YotsuyaQR[25][8] = {
        {0b01111111,0b01000001,0b01011101,0b01011101,0b01011101,0b01000001,0b01111111,0b00000000},
        {0b11010101,0b10111101,0b11100111,0b00001101,0b11100110,0b00011010,0b01000011,0b10110010},
        {0b01010000,0b00100101,0b01101000,0b10110010,0b01100100,0b10010010,0b11000111,0b10110110},
        {0b11101000,0b00001000,0b11000101,0b10001100,0b11101111,0b00000000,0b01111111,0b01000001},
        {0b01011101,0b01011101,0b01011101,0b01000001,0b01111111,0b00000000,0b00000000,0b00000000},
    
        {0b11010110,0b01100100,0b10100110,0b00001000,0b10001100,0b10100001,0b01010101,0b01101000},
        {0b00110010,0b11000111,0b00110000,0b01000101,0b11101000,0b11010010,0b00011111,0b01010111},
        {0b00011001,0b01010110,0b11110000,0b00110011,0b11111001,0b00100001,0b01000111,0b01100100},
        {0b00001011,0b01100110,0b01001100,0b01101000,0b00111000,0b01100010,0b00011111,0b11110100},
        {0b01000011,0b11011010,0b10100011,0b01011110,0b11010101,0b00000000,0b00000000,0b00000000},
    
        {0b10111001,0b11100110,0b01111010,0b10101110,0b10100100,0b10110111,0b01010101,0b01000101},
        {0b00010000,0b01001100,0b10011100,0b11111111,0b00111101,0b00100110,0b11001111,0b10100010},
        {0b10011101,0b01111101,0b00100101,0b00100000,0b11001100,0b10001100,0b00111100,0b10000111},
        {0b00100000,0b11110001,0b01011101,0b11101111,0b00101010,0b01010101,0b00010101,0b10110100},
        {0b00110001,0b11101100,0b00110111,0b01101001,0b11010101,0b00000000,0b00000000,0b00000000},
    
        {0b11000001,0b01011101,0b01001110,0b01011100,0b01001101,0b01010010,0b11010101,0b00000001},
        {0b10110011,0b01110111,0b11001010,0b10101110,0b01111101,0b01110000,0b10110111,0b00110010},
        {0b11110001,0b00110001,0b10110110,0b10010011,0b11101010,0b01010011,0b11001101,0b11111101},
        {0b10010101,0b00110101,0b00010100,0b10110100,0b11111100,0b00011000,0b01010110,0b00011011},
        {0b11110111,0b11110100,0b01001100,0b10110100,0b11000100,0b00000000,0b00000000,0b00000000},
    
        {0b00011111,0b00010000,0b00010111,0b00010111,0b00010111,0b00010000,0b00011111,0b00000000},
        {0b00000000,0b00000101,0b00011010,0b00011111,0b00000100,0b00001100,0b00000011,0b00010000},
        {0b00010000,0b00010011,0b00000001,0b00011100,0b00001001,0b00011101,0b00001111,0b00010000},
        {0b00011010,0b00000101,0b00001011,0b00000011,0b00011101,0b00000101,0b00001011,0b00010101},
        {0b00011001,0b00011010,0b00000011,0b00000000,0b00011100,0b00000000,0b00000000,0b00000000}
    };
};

#endif // SSD1309_H