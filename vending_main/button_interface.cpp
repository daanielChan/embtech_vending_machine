#include "button_interface.h"
#include <Arduino.h> 

using namespace driver;

btn_interface_t::btn_interface_t (pins_t pins) {
  m_pins = pins;
  pinMode(m_pins.left, INPUT_PULLUP);
  pinMode(m_pins.right, INPUT_PULLUP);
  pinMode(m_pins.top, INPUT_PULLUP);
  pinMode(m_pins.down, INPUT_PULLUP);
  pinMode(m_pins.center, INPUT_PULLUP);
}

btn_interface_t::btn_action_t btn_interface_t::get_action() {
  btn_action_t ret_val = btn_action_t::NONE;

  if (digitalRead(m_pins.left)) {
    ret_val = btn_action_t::LEFT;
  } else if (digitalRead(m_pins.right)){
    ret_val = btn_action_t::RIGHT;
  } else if (digitalRead(m_pins.top)){
    ret_val = btn_action_t::TOP;
  } else if (digitalRead(m_pins.left)){
    ret_val = btn_action_t::DOWN;
  } else if (digitalRead(m_pins.center)){
    ret_val = btn_action_t::CENTER;
  }

  return ret_val;
}