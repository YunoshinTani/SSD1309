author  Yunoshin Tani
version 1.0.0
date    2025/02/27

## 概要 (about)
ステッピングモータードライバーIC "ULN2003APG" を制御するライブラリです。  
GitHubのリンク [YunoshinTani/SSD1309](https://github.com/YunoshinTani/SSD1309.git)  
mbedOSでのみ動作します。開発環境はSTM32F446REです。

## 機能 (functionalities)
- **oled(PinName sda, PinName scl, PinName address)**
コンストラクタです。I2C通信に使用するSDA,SCLピンを渡します。addressは0x3Cが初期設定値です。
- **void init()**
初期設定をします。
- **bool text()**  
通信のテストをします。返り値が0であれば通信成功です。
- **void clear()**  
ディスプレイのピクセルをすべて消します。
- **void fill()**  
ディスプレイのピクセルをすべて表示します。
- **void drawPixel(uint8_t x, uint8_t y)**
指定した座標に点を表示します。
- **void drawLine(uint8_t x, uint8_t y)**
指定した座標に線を表示します。必ずどちらかを0にしてください。
- **void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)**
四角形(輪郭のみ)を表示します。指定する座標は左下の座標です。横幅wと高さhを指定します。
- **void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)**
四角形(塗りつぶし)を表示します。指定する座標は左下の座標です。横幅wと高さhを指定します。
- **void drawCircle(uint8_t x, uint8_t y, uint8_t r)**
円(輪郭のみ)を表示します。指定する座標は円の中心です。半径rを指定します。
- **void fillCircle(uint8_t x, uint8_t y, uint8_t r)**
円(塗りつぶし)を表示します。指定する輪郭は円の中心です。半径rを指定します。
- **void drawInt(double data, uint8_t x, uint8_t y, const char *option)**
数字を表示します。optionにフォーマット演算子(%dなど)を指定できます。初期設定値は"%d"です。センサーの数字を表示する等に便利です。
- **void drawText(const char *text, uint8_t x, uint8_t y)**
文章を表示します。
- **void drawQR(uint8_t data[25][8], uint8_t x, uint8_t y)**
QRコードを表示します。

> [!NOTE]
> スクロールにも対応予定です。

## コード例 (example)
```cpp
#include <SSD1309.h>

oled display1(PB_9, PB_8);

int main() {
    display1.init();
    display1.clear();
    while (true) {
        display1.drawText("HelloWorld!", 24, 4);
    }
}
```
