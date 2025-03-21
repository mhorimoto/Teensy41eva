# Teensy41eva

Teensy4.1の練習用プログラム群

## t001

Blink

## t002

Serial出力テスト Hello World

## t003

Analog Write テスト

## t004

DhcpAddressPrinter

## t005

LED Matrix 点灯テスト

## t006

LED Matrix 点灯テスト

## t007

制御ボタンスイッチ D14,D15,D16 の割り込みテストプログラム

## t008

LCD_I2Cと t007 を組み合わせる。

## t009

Key switch operation by scan mode  
t008 を32個のスイッチに派生させる。  
32個スイッチは割り込みを使わずスキャン形式で対応する。

## t010

TimerInterruption test.

## t011

I2C with TimerInterruption

## t012

t011を使って押し下げたマトリックススイッチに対応したLEDのみを点灯する。

## t013

スタティック点灯によりROW/COLのLEDテスト

## t014

t013に加えて、３ボタンによりメモリクリアやメモリ内容表示など付帯する機能の試験。

## t015

SNMPの試験

## t016

VR(A17)のアナログ入力試験

## t017

EEPROMの試験
既存M302Kのeepromプログラムが使えるか試験

## How to make new project by CLI

```pio project init -b teensy41 -e teensy41 --ide vscode -d [directory name]```


