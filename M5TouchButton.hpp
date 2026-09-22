#pragma once
#include <M5Unified.h>

/**
 * @brief M5 Stack CoreS3用のタッチボタンライブラリ
 * @note 依存関係 : M5Unifiedライブラリ
 */
class M5TouchButton {
private:
  int16_t x_, y_, w_, h_;
  bool currentState_;
  bool lastState_;
  uint32_t lastChangeTime_;
  uint32_t debounceTime_;
  const char* label_;
  uint32_t color_;
  uint32_t textColor_;
  uint32_t lastDrawTime_;
  /**
   * @brief Draw the button on the screen.
   *
   * @param label The text to display on the button.
   * @param color The color of the button's border.
   * @param textColor The color of the text.
   */
  void draw(const char* label, uint32_t color = TFT_WHITE, uint32_t textColor = TFT_WHITE) {
    M5.Display.drawRect(x_, y_, w_, h_, color);
    M5.Display.setTextColor(textColor);
    M5.Display.setTextDatum(middle_center);
    M5.Display.drawString(label, x_ + (w_ / 2), y_ + (h_ / 2));
  }

public:
  /**
   * @brief Construct a new M5TouchButton object
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @param debounce
   */
  M5TouchButton(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t debounce = 20)
      : x_(x), y_(y), w_(w), h_(h), currentState_(false), lastState_(false), lastChangeTime_(0), debounceTime_(debounce) {}

  void begin(const char* label, uint32_t color = TFT_WHITE, uint32_t textColor = TFT_WHITE) {
    label_        = label;
    color_        = color;
    textColor_    = textColor;
    lastDrawTime_ = 0;
  }

  /**
   * @brief Update the button state. This should be called in the main loop.
   */
  void update() {
    lastState_     = currentState_;
    bool isTouched = false;

    // タッチされているポイントを全てチェック
    std::size_t count = M5.Touch.getCount();
    for (std::size_t i = 0; i < count; ++i) {
      auto detail = M5.Touch.getDetail(i);
      if (detail.isPressed()) {
        // タッチ座標が設定した矩形領域内にあるか判定
        if (detail.x >= x_ && detail.x <= (x_ + w_) && detail.y >= y_ && detail.y <= (y_ + h_)) {
          isTouched = true;
          break;
        }
      }
    }

    // デバウンス処理
    if (isTouched != currentState_) {
      if (millis() - lastChangeTime_ > debounceTime_) {
        currentState_   = isTouched;
        lastChangeTime_ = millis();
      }
    } else {
      lastChangeTime_ = millis();
    }
    draw(label_, color_, textColor_);
  }

  /**
   * @brief   Get the button's current state.
   *
   * @return true/false
   */
  bool isPressed() const { return currentState_; }
  /**
   * @brief   Get the button's current state.
   *
   * @return true/false
   */
  bool isReleased() const { return !currentState_; }
  /**
   * @brief   Get the button's state change.
   *
   * @return true if the button was pressed, false otherwise.
   */
  bool wasPressed() const { return currentState_ && !lastState_; }
  /**
   * @brief   Get the button's state change.
   *
   * @return true if the button was released, false otherwise.
   */
  bool wasReleased() const { return !currentState_ && lastState_; }
};
