#include "led_matrix.h"

led_matrix_t::led_matrix_t(uint8_t row_pins[8], uint8_t col_pins[5]) {
  for (int i = 0; i < 8; i++) {
    this->m_row_pins[i] = row_pins[i];
  }
  for (int i = 0; i < 5; i++) {
    this->m_col_pins[i] = col_pins[i];
  }
}

void led_matrix_t::begin() {
  for (int i = 0; i < 8; i++) {
    pinMode(m_row_pins[i], OUTPUT);
    digitalWrite(m_row_pins[i], LOW);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(m_col_pins[i], OUTPUT);
    digitalWrite(m_col_pins[i], LOW);
  }
}

void led_matrix_t::set_led(uint8_t row, uint8_t col, bool state) {
  if (row >= 8 || col >= 5) return;

  if (state) {
    digitalWrite(m_row_pins[row], LOW);
    digitalWrite(m_col_pins[col], HIGH);
  } else {
    digitalWrite(m_row_pins[row], HIGH);
    digitalWrite(m_col_pins[col], LOW);
  }
}

void led_matrix_t::set_led(led_state_t led_state) {
  set_led(led_state.col, led_state.row, led_state.state);
}

void led_matrix_t::clear() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(m_row_pins[i], LOW);
  }
  for (int i = 0; i < 5; i++) {
    digitalWrite(m_col_pins[i], HIGH);
  }
}
