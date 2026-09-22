# M5TouchButton

A simple, lightweight custom touch button library for the **M5Stack CoreS3** (and other touch-compatible M5 devices).

This library works alongside `M5Unified` and allows you to easily map any rectangular area on the touch screen into a functional button. It provides the same intuitive methods (`wasPressed()`, `isPressed()`, etc.) as the standard physical buttons (like `M5.BtnA`).

## Features

- **Custom Mapping:** Define buttons anywhere on the screen by specifying X/Y coordinates, width, and height.
- **Built-in Debouncing:** Prevents false triggers with customizable debounce timing.
- **Easy UI Integration:** Automatically draws the button border and centered text label.
- **M5Unified Style API:** Uses familiar methods (`isPressed`, `isReleased`, `wasPressed`, `wasReleased`).

## Dependencies

- [M5Unified](https://github.com/m5stack/M5Unified?utm_source=gemini)

## Installation

1. Download or copy the `M5TouchButton.h` file into your project directory (or Arduino `libraries` folder).
2. Include it in your main sketch: `#include "M5TouchButton.h"`

## Usage / Example

Here is a basic example of how to implement `M5TouchButton` in your project (`main.cpp` or `.ino`):

```cpp
#include <M5Unified.h>
#include "M5TouchButton.h"

// 1. Create a button instance: X=110, Y=80, Width=100, Height=80
M5TouchButton myButton(110, 80, 100, 80);

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Display.setTextSize(2);

    // 2. Initialize the button with a label and colors
    myButton.begin("Btn 1", TFT_GREEN, TFT_WHITE);

    M5.Display.setCursor(0, 200);
    M5.Display.println("Ready.");
}

void loop() {
    // 3. Update M5 system and the custom button
    M5.update();
    myButton.update(); // Updates state and redraws the button UI

    // 4. Handle button events
    if (myButton.wasPressed()) {
        M5.Display.fillRect(0, 200, 320, 40, TFT_BLACK);
        M5.Display.setCursor(0, 200);
        M5.Display.println("Custom Button Pressed!");
    }

    delay(10);
}

```

## API Reference

### Constructor

`M5TouchButton(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t debounce = 20)`
Creates a new touch button.

- `x`: X-coordinate of the top-left corner.
- `y`: Y-coordinate of the top-left corner.
- `w`: Width of the button.
- `h`: Height of the button.
- `debounce`: Debounce time in milliseconds (Default is 20ms).

### Initialization

`void begin(const char* label, uint32_t color = TFT_WHITE, uint32_t textColor = TFT_WHITE)`
Sets up the visual properties of the button.

- `label`: The text to display inside the button.
- `color`: The color of the button's rectangular border.
- `textColor`: The color of the text label.

### Core Methods

- `void update()`: Updates the touch state and handles debouncing. **Must be called in the main `loop()**`. _Note: This method also handles drawing the button to the screen._
- `bool isPressed()`: Returns `true` if the button is currently being held down.
- `bool isReleased()`: Returns `true` if the button is currently not touched.
- `bool wasPressed()`: Returns `true` only once in the frame the button is first touched.
- `bool wasReleased()`: Returns `true` only once in the frame the button is released.
