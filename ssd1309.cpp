/**
 * @file ssd1309.cpp
 * @author Yunoshin Tani (taniyunoshin@gmail.com)
 * @brief SSD1309 OLED display driver
 * @details This is a library for the SSD1309 OLED display driver.
 * @version α2.1.0
 * @since 2025/04/26
 * @date 2025/04/29
 * @copyright Copyright (c) 2025
 */

#include "ssd1309.hpp"

SSD1309::SSD1309(PinName sda, PinName scl, uint8_t address) : _i2c(sda, scl) {
    _address = address << 1;
}

bool SSD1309::command(uint8_t cmd) {
    char buf[2] = {0x00, cmd};
    return (_i2c.write(_address, buf, 2) == 0) ? true : false;
}

bool SSD1309::send(uint8_t data) {
    char buf[2] = {0x40, data};
    return (_i2c.write(_address, buf, 2) == 0) ? true : false;
}

void SSD1309::init()
{
    _i2c.frequency(4e5);

    // 初期化
    command(0xAE); // ディスプレイOFF
    command(0xD5); // ディスプレイクロック分周比/振動数設定
    command(0x80); // ディスプレイクロック分周比/振動数設定
    command(0xA8); // マルチプレクス比設定
    command(0x3F); // マルチプレクス比設定
    command(0xD3); // ディスプレイオフセット設定
    command(0x00); // ディスプレイオフセット設定
    command(0x40); // ディスプレイ開始行設定
    command(0x8D); // 充電ポンプ設定
    command(0x14); // 充電ポンプ設定
    command(0x20); // メモリアドレスモード設定
    command(0x00); // メモリアドレスモード設定
    command(0xA1); // セグメントリマップ設定
    command(0xC8); // コモンリマップ設定
    command(0xDA); // ハードウェアコンフィギュレーション設定
    command(0x12); // ハードウェアコンフィギュレーション設定
    command(0x81); // コントラスト設定
    command(0xCF); // コントラスト設
    command(0xD9); // プリチャージ設定
    command(0xF1); // プリチャージ設定
    command(0xDB); // VCOMHデセレクトレベル設定
    command(0x40); // VCOMHデセレクトレベル設定
    command(0xA4); // 全画面表示ON（通常表示）
    command(0xA6); // 通常表示モード
    command(0xAF); // ディスプレイON
}

bool SSD1309::test() {
    return command(0xAF);
}

void SSD1309::clear() {
    for (uint8_t i1=0; i1<8; i1++) {
        setCursor(0, i1);
        for (uint8_t i2=0; i2<16; i2++) {
            send(0x00);
        }
    }
}

void SSD1309::fill() {
    for (uint8_t i1=0; i1<8; i1++) {
        setCursor(0, i1);
        for (uint8_t i2=0; i2<16; i2++) {
            send(0xFF);
        }
    }
}

void SSD1309::setCursor(uint8_t x, uint8_t y) {
    command(0xB0 + y);
    command(0x00 + (x & 0x0F));
    command(0x10 + ((x >> 4) & 0x0F));
}

void SSD1309::drawPixel(uint8_t x, uint8_t y) {
    setCursor(x, y);
    send(0x01);
}

void SSD1309::drawLine(uint8_t x, uint8_t y) {
    // Not implemented
}

void SSD1309::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    // Not implemented
}

void SSD1309::drawRect2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    // Not implemented
}

void SSD1309::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    // Not implemented
}

void SSD1309::fillRect2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    // Not implemented
}

void SSD1309::drawCircle(uint8_t x, uint8_t y, uint8_t r) {
    // Not implemented
}

void SSD1309::fillCircle(uint8_t x, uint8_t y, uint8_t r) {
    // Not implemented
}

void SSD1309::drawInt(int data, uint8_t row, uint8_t x, const char *option) {
    char buf[10];
    sprintf(buf, option, data);
    drawText(buf, x, row);
}

void SSD1309::drawChar(char data) {
    for (uint8_t i=0; i<5; i++) {
        send(SSD1309::FONT5x8[data - 32][i]);
    }
    send(0x00);
}

void SSD1309::drawText(const char *text, uint8_t row, uint8_t x) {
    setCursor(x, row);
    while (*text) {
        drawChar(*text++);
    }
}

void SSD1309::drawText(const char *text, uint8_t row, Align align) {
    if (align == Align::Left) setCursor(0, row);
    else if (align == Align::Center) setCursor((128-strlen(text)*6)/2, row);
    else if (align == Align::Right) setCursor(128-strlen(text)*6, row);
    else setCursor(0, row);
    while (*text) {
        drawChar(*text++);
    }
}

// 1 cell == 8 * 8 pixel
void SSD1309::drawData(const uint8_t data[][8], uint8_t x, uint8_t y, uint8_t max_row, uint8_t max_column) {
    for (uint8_t row=0; row<max_row; row++) {
        for (uint8_t column=0; column<max_column; column++) {
            setCursor(column*8 + x, row + y);
            for (uint8_t i=0; i<8; i++) {
                send(data[row*max_column + column][i]);
            }
        }
    }
}

void SSD1309::drawQR(uint8_t data[25][8], uint8_t x, uint8_t y) {
    drawData(data, x, y, 5, 5);
}

