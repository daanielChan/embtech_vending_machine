#pragma once

namespace driver {
class btn_interface_t final {
public:
  enum class btn_action_t {
    LEFT,
    RIGHT,
    TOP,
    DOWN,
    CENTER,
    NONE
  };

  typedef struct {
    int left;
    int right;
    int top;
    int down;
    int center;
  } pins_t;

  btn_interface_t(pins_t pins);
  btn_action_t get_action();


private:
  pins_t m_pins;
};
}