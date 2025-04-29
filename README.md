# OLEDディスプレイIC SSD1309 制御用ライブラリ (SSD1309_OLED_Driver)

## 概要 (about)

有機ELディスプレイ(OLED)を制御するIC "SSD1309" を制御するライブラリです。  
[コードの例](#コード例-example)を見たら、使い方は大体わかると思います。  
GitHubのリンク : [YunoshinTani/SSD1309_OLED_Driver](https://github.com/YunoshinTani/SSD1309_OLED_Driver.git)

> [!NOTE]
> 使用しているライブラリはmbedCANです。開発環境はSTM32F446REマイコンです。

## 機能 (functionalities)

### 重要な関数

- **`oled(PinName sda, PinName scl, PinName address = 0x3c)`**  
コンストラクタです。I2C通信に使用するSDA,SCLピンとアドレスを指定します。addressは0x3Cが初期設定値です。
- **`void init()`**  
ディスプレイの初期設定をします。やっておかないと動かないので注意。
- **`void clear()`**  
ディスプレイのピクセルをすべて消します。
- **`void fill()`**  
ディスプレイのピクセルをすべて表示します。
- **`void drawText(const char *text, uint8_t row, Align align = Left)`**  
文章を表示します。一番使えるやつです。例えば、alignに**Center**を指定すると、中央揃えにしてくれます。初期値はLeftです。
- **`void drawText(const char *text, uint8_t row, uint8_t x)`**  
上の関数の最後の引数を数字にすると、その引数のx座標から文章を表示します。細かい位置指定が必要な時に使えます。
- **`void drawInt(int data, uint8_t row, uint8_t x, const char *option)`**  
数字を表示します。optionにフォーマット指定子(%dなど)を指定できます。初期設定値は"%d"です。センサーの数字を表示する等に便利です。
- **`void drawData(const uint8_t data[][8], uint8_t x=0, uint8_t y=0, uint8_t max_row=8, uint8_t max_column=16)`**  
ピクセルのデータを描画します。絵を描画したいときに使えます。ピクセルの配列はなんか癖が強いので注意してね。
- **`void drawQR(uint8_t data[][], uint8_t x, uint8_t y)`**  
QRコードを表示します。今は人力です。いつかQRコードを生成するようにしてやります。
- **`bool test()`**  
通信のテストをします。返り値が1であれば通信成功です。

> [!IMPORTANT]
> `init()`を実行しないとディスプレイが使えません。注意してね。

### 未実装の関数 (まだ使えないので注意)

- **`void drawLine(uint8_t x, uint8_t y)`**  
指定した座標に線を表示します。必ずどちらかを0にしてください。これ一次関数の式にすればいいんじゃね... いつかやります。
- **`void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)`**  
四角形(輪郭のみ)を表示します。指定する座標は左下の座標です。横幅wと高さhを指定します。
- **`void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)`**  
四角形(塗りつぶし)を表示します。指定する座標は左下の座標です。横幅wと高さhを指定します。
- **`void drawCircle(uint8_t x, uint8_t y, uint8_t r)`**  
円(輪郭のみ)を表示します。指定する座標は円の中心です。半径rを指定します。
- **`void fillCircle(uint8_t x, uint8_t y, uint8_t r)`**  
円(塗りつぶし)を表示します。指定する輪郭は円の中心です。半径rを指定します。

## コード例 (example)

```cpp
#include "ssd1309.hpp"

Oled oled1(PB_9, PB_8);

int main() {
    int example_value1 = 100;
    int example_value2 = 200;
    oled1.init();
    oled1.fill();
    oled1.clear();
    while (true) {
        oled1.drawText("HelloWorld!", 1, Oled::Align::Center); // 文字列を1行目に中央揃えで表示
        oled1.drawText("I like Sushi very much", 3); // 文字列を3行目に左揃え(デフォルト)で表示
        oled1.drawText("Sensor Value:", 5, 20); // 文字列をX座標20の位置から表示
        oled1.drawInt(example_value1, 6, 0); // 値(int型)をX座標0の位置から表示
        oled1.drawText(",", 6, 30); // 文字列をX座標20の位置から表示
        oled1.drawInt(example_value2, 6, 60);
        oled1.drawText("GoodLuck!!", 7, Oled::Align::Right); // 行は0から7まで
    }
}
```

> [!NOTE]
> 22文字以上の文字列は次の行に改行されます。

## このライブラリについて (about this library)

**author**  : Yunoshin Tani  
**version** : α2.1.0  
**since**   : 2025/04/26  
**date**    : 2025/04/28  

## このファイルについて (about this file)

**author**  : Yunoshin Tani  
**version** : α2.1.0  
**since**   : 2025/04/26  
**date**    : 2025/04/28  

> [!NOTE]
> まだアルファ版です。
> スクロールにも対応予定です。
