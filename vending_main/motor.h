#pragma once
#include <Wire.h>
#include "PCF8575.h"

namespace driver {
  class motor_t final {
    public:
      motor_t();
      void set_level(int num, bool level);

    private:
      PCF8575* m_io_exp[2]; 
      uint8_t m_pins [8] = {22, 23, 24, 25, 26, 27, 28, 29};
  };
}