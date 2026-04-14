#define DISABLE_CODE_FOR_RECEIVER
#define IR_TX_PIN 44
#include "M5Cardputer.h"
#include <IRremote.hpp>
#include "codes.h"
#include "NotoSansBold15.h"
M5Canvas sprite(&M5Cardputer.Display);

const uint32_t SAMSUNG_POWER = 0xE0E040BF;
const uint32_t SAMSUNG_VOL_UP = 0xE0E0E01F;
const uint32_t SAMSUNG_VOL_DOWN = 0xE0E0D02F;
const uint32_t SAMSUNG_MUTE = 0xE0E0F00F;
const uint32_t SAMSUNG_CH_UP = 0xE0E048B7;
const uint32_t SAMSUNG_CH_DOWN = 0xE0E008F7;
const uint32_t SAMSUNG_LEFT = 0xE0E0A659;
const uint32_t SAMSUNG_UP = 0xE0E006F9;
const uint32_t SAMSUNG_RIGHT = 0xE0E046B9;
const uint32_t SAMSUNG_DOWN = 0xE0E08679;
const uint32_t SAMSUNG_OK = 0xE0E016E9;
const uint32_t SAMSUNG_HOME = 0xE0E058A7;
const uint32_t SAMSUNG_EXIT = 0xE0E0B44B;

bool tcom = false;
bool btn[23] = { 0 };

const unsigned short c1 = 0x026E;
const unsigned short c2 = 0x0B0C;
const unsigned short c3 = 0x7075;
const unsigned short c4 = 0x5800;
const unsigned short c5 = 0x18E3;

const int BUTTON_COUNT = 23;
const int xPos[23] = { 178, 150, 178, 206, 150, 178, 206, 150, 178, 206, 118, 118, 118, 90, 90, 6, 32, 58, 32, 32, 150, 206, 90 };
const int yPos[23] = { 100, 4, 4, 4, 36, 36, 36, 68, 68, 68, 36, 92, 4, 36, 92, 78, 52, 78, 104, 78, 100, 100, 4 };
const int width[23] = { 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 24, 24, 24, 24, 24, 26, 26, 26 };
const int height[23] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 38, 38, 30, 38, 38, 24, 24, 24, 24, 24, 30, 30, 30 };
const char* lbl[23] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "-", "M", "+", "-", "<", "", ">", "", "OK", "", "EX" };
const unsigned short col[23] = { c1, c1, c1, c1, c1, c1, c1, c1, c1, c1, c2, c2, c2, c2, c2, c3, c3, c3, c3, c3, c4, c4, c5 };
unsigned short color = 0;


void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setBrightness(70);
  sprite.createSprite(240, 135);

  sprite.setTextDatum(middle_center);

  IrSender.begin(DISABLE_LED_FEEDBACK);  // Start with IR_SEND_PIN as send pin
  IrSender.setSendPin(IR_TX_PIN);

  draw();
}

void draw() {
  sprite.fillSprite(BLACK);
  sprite.loadFont(NotoSansBold15);
  sprite.fillRoundRect(4, 48, 80, 82, 8, 0x0861);
  sprite.setTextColor(TFT_SILVER, TFT_BLACK);
  sprite.fillRect(4, 4 + (tcom * 18), 4, 13, TFT_ORANGE);
  sprite.drawString("SAMSUNG", 47, 12);
  sprite.drawString("T-COM", 37, 30);
  for (int i = 0; i < BUTTON_COUNT; i++) {
    if (btn[i])
      color = TFT_ORANGE;
    else
      color = col[i];
    sprite.fillRoundRect(xPos[i], yPos[i], width[i], height[i], 3, color);
    sprite.setTextColor(TFT_SILVER, color);
    sprite.drawString(lbl[i], xPos[i] + width[i] / 2, yPos[i] + height[i] / 2);
  }
  sprite.unloadFont();
  sprite.setTextColor(TFT_SILVER, TFT_BLACK);
  sprite.drawString("VOLOS REMOTE", 44, 44);
  sprite.drawString("CH", 104, 84);
  sprite.drawString("VOL", 130, 84);
  sprite.fillArc(103, 19, 10, 8, 0, 230, TFT_RED);
  sprite.fillArc(103, 19, 10, 8, 310, 359, TFT_RED);
  sprite.fillRect(102, 8, 3, 10, TFT_RED);
  sprite.fillRect(157, 112, 12, 12, TFT_SILVER);
  sprite.fillRect(160, 116, 5, 9, c4);
  sprite.fillTriangle(154, 112, 171, 112, 162, 106, TFT_SILVER);
  sprite.pushSprite(0, 0);
}

void loop() {
  M5Cardputer.update();

  if (M5Cardputer.BtnA.wasPressed()) {
    IrSender.sendSAMSUNG(SAMSUNG_POWER, 32);
    delay(30);
    draw();
  }

  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_FN)) {
      tcom = !tcom;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB)) {
      IrSender.sendRaw(on, sizeof(on) / sizeof(on[0]), 38);
      btn[22] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('0')) {
      IrSender.sendRaw(zero, sizeof(zero) / sizeof(zero[0]), 38);
      btn[0] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('1')) {
      IrSender.sendRaw(one, sizeof(one) / sizeof(one[0]), 38);
      btn[1] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('2')) {
      IrSender.sendRaw(two, sizeof(two) / sizeof(two[0]), 38);
      btn[2] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('3')) {
      IrSender.sendRaw(three, sizeof(three) / sizeof(three[0]), 38);
      btn[3] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('4')) {
      IrSender.sendRaw(four, sizeof(four) / sizeof(four[0]), 38);
      btn[4] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('5')) {
      IrSender.sendRaw(five, sizeof(five) / sizeof(five[0]), 38);
      btn[5] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('6')) {
      IrSender.sendRaw(six, sizeof(six) / sizeof(six[0]), 38);
      btn[6] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('7')) {
      IrSender.sendRaw(seven, sizeof(seven) / sizeof(seven[0]), 38);
      btn[7] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('8')) {
      IrSender.sendRaw(eight, sizeof(eight) / sizeof(eight[0]), 38);
      btn[8] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('9')) {
      IrSender.sendRaw(nine, sizeof(nine) / sizeof(nine[0]), 38);
      btn[9] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('s')) {
      if (tcom)
        IrSender.sendRaw(vup, sizeof(vup) / sizeof(vup[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_VOL_UP, 32);
      btn[10] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('z')) {
      if (tcom)
        IrSender.sendRaw(vdwn, sizeof(vdwn) / sizeof(vdwn[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_VOL_DOWN, 32);
      btn[11] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('m')) {
      if (tcom)
        IrSender.sendRaw(mute, sizeof(mute) / sizeof(mute[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_MUTE, 32);
      btn[12] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('f')) {
      if (tcom)
        IrSender.sendRaw(cup, sizeof(cup) / sizeof(cup[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_CH_UP, 32);
      btn[13] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('c')) {
      if (tcom)
        IrSender.sendRaw(cdwn, sizeof(cdwn) / sizeof(cdwn[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_CH_DOWN, 32);
      btn[14] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(',')) {
      if (tcom)
        IrSender.sendRaw(left, sizeof(left) / sizeof(left[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_LEFT, 32);
      btn[15] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(';')) {
      if (tcom)
        IrSender.sendRaw(up, sizeof(up) / sizeof(up[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_UP, 32);
      btn[16] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('/')) {
      if (tcom)
        IrSender.sendRaw(right, sizeof(right) / sizeof(right[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_RIGHT, 32);
      btn[17] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('.')) {
      if (tcom)
        IrSender.sendRaw(down, sizeof(down) / sizeof(down[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_DOWN, 32);
      btn[18] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
      if (tcom)
        IrSender.sendRaw(ok, sizeof(ok) / sizeof(ok[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_OK, 32);
      btn[19] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(' ')) {
      if (tcom)
        IrSender.sendRaw(home, sizeof(home) / sizeof(home[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_HOME, 32);
      btn[20] = 1;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)) {
      if (tcom)
        IrSender.sendRaw(ex, sizeof(ex) / sizeof(ex[0]), 38);
      else
        IrSender.sendSAMSUNG(SAMSUNG_EXIT, 32);
      btn[21] = 1;
    }

    draw();
    delay(60);
    for (int i = 0; i < BUTTON_COUNT; i++)
      btn[i] = 0;
    draw();
  }
}
