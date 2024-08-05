#include "motor.h"
#include <Arduino.h>

using namespace driver;

motor_t::motor_t() {
  for (int i = 0; i < 2; i++) {
    m_io_exp [i] = new PCF8575;
    m_io_exp [i] ->begin();
  }
}


void motor_t::set_level(int num, bool level) {
  int index_expander = 0;
  if (num < 8) {
    digitalWrite(m_pins[num], level);
  } else if (num >= 8 && num < 24) {
    m_io_exp[0]->write((num - 8), level);
  } else if (num >= 24 && num < 40) {
    m_io_exp[1]->write((num - 24), level);
  }
}
