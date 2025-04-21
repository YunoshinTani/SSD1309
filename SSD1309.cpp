/**
 * @file SSD1309.cpp
 * @author Yunoshin Tani (taniyunoshin@gmail.com)
 * @brief SSD1309 OLED display driver
 * @details This is a library for the SSD1309 OLED display driver.
 * @version 1.0.0
 * @date 2025/02/27
 * @copyright Copyright (c) 2025
 */

#include "SSD1309.hpp"

Oled::Oled(PinName sda, PinName scl, uint8_t address) : _i2c(sda, scl) {
    _address = address << 1;
}

bool Oled::command(uint8_t cmd) {
    char buf[2] = {0x00, cmd};
    return (_i2c.write(_address, buf, 2) != 0) ? true : false;
}

bool Oled::send(uint8_t data) {
    char buf[2] = {0x40, data};
    return (_i2c.write(_address, buf, 2) != 0) ? true : false;
}

void Oled::init()
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

bool Oled::test() {
    return _i2c.write(_address, 0x00, 1);
}

void Oled::clear() {
    for (int i3=0; i3<8; i3++) {
        setCursor(0, i3);
        for (int i2=0; i2<16; i2++) {
            for (int i1=0; i1<8; i1++) {
                send(0x00);
            }
        }
    }
}

void Oled::fill() {
    for (int i3=0; i3<8; i3++) {
        setCursor(0, i3);
        for (int i2=0; i2<16; i2++) {
            for (int i1=0; i1<8; i1++) {
                send(0xFF);
                // ThisThread::sleep_for(5ms); // for debug
            }
        }
    }
}

void Oled::setCursor(uint8_t x, uint8_t y) {
    command(0xB0 + y);
    command(0x00 + (x & 0x0F));
    command(0x10 + ((x >> 4) & 0x0F));
}

void Oled::drawPixel(uint8_t x, uint8_t y) {
    setCursor(x, y);
    send(0x01);
}

void Oled::drawLine(uint8_t x, uint8_t y) {
    // Not implemented
}

void Oled::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    // Not implemented
}

void Oled::drawRect2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    // Not implemented
}

void Oled::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    // Not implemented
}

void Oled::fillRect2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    // Not implemented
}

void Oled::drawCircle(uint8_t x, uint8_t y, uint8_t r) {
    // Not implemented
}

void Oled::fillCircle(uint8_t x, uint8_t y, uint8_t r) {
    // Not implemented
}

void Oled::drawInt(int data, uint8_t x, uint8_t y, const char *option) {
    char buf[10];
    sprintf(buf, option, data);
    drawText(buf, x, y);
}

void Oled::drawChar(char data) {
    for (uint8_t i=0; i<5; i++) {
        send(Oled::FONT5x8[data - 32][i]);
    }
    send(0x00);
}

void Oled::drawText(const char *text, uint8_t x, uint8_t y) {
    setCursor(x, y);
    while (*text) {
        drawChar(*text++);
    }
}

void Oled::drawQR(uint8_t x, uint8_t y) {
    for (uint8_t py=0; py<5; py++) {
        for (uint8_t px=0; px<5; px++) {
            setCursor(px * 8 + x, py + y);
            for (uint8_t i=0; i<8; i++) {
                send(YotsuyaQR[px + 5 * py][i]);
            }
        }
    }
}

void Oled::drawQR(uint8_t data[25][8] , uint8_t x, uint8_t y) {
    for (uint8_t py=0; py<5; py++) {
        for (uint8_t px=0; px<5; px++) {
            setCursor(px * 8 + x, py + y);
            for (uint8_t i=0; i<8; i++) {
                send(data[px + 5 * y][i]);
            }
        }
    }
}
