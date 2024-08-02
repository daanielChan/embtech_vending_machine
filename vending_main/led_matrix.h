#pragma once

#include <Arduino.h>
#include <stdbool.h>

class led_matrix_t {
  public:
    typedef struct {
      uint8_t row;
      uint8_t col;
      bool state;
    }led_state_t;

    led_matrix_t(uint8_t row_pins[8], uint8_t col_pins[5]);

    void begin();
    void set_led (uint8_t row, uint8_t col, bool state);
    void set_led (led_state_t led_state);

    void clear();

  private:
    uint8_t m_row_pins[8];
    uint8_t m_col_pins[5];

    void update();
};