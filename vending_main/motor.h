#pragma once
#include <Wire.h>


namespace driver: {
  class motor_t final {
    public:
      motor_t(TwoWire &wire);
      void set_level(int num, bool level);

    private:
      TwoWire *m_wire;
      //tca9548a* m_io_exp[5]; colocar IO expanders aqui
  };
}