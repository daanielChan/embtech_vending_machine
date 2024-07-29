#pragma once
#include "TCA9548A.h"


namespace driver: {
  class motor_t final {
    public:
      motor_t();
      void set_level(int num, bool level);

    private:
      //tca9548a* m_io_exp[5]; colocar IO expanders aqui
  };
}