/* ----------------------------------- Inclusões ----------------------------------- */ 
#include "button_interface.h"
#include "timer.h"

using namespace driver;
/* ----------------------------------- Configurações ----------------------------------- */ 
constexpr uint32_t tempo_colunas_s [5] = {30000, 30000, 30000, 30000, 30000}; 

/* ----------------------------------- Variaveis ----------------------------------- */ 
constexpr int PRESENCE_SENSOR_PIN = A7;

typedef enum {
  state_idle = 0,
  state_select_product,
  state_moving_motor,
  state_verify_money
} states_e;

states_e m_state;

btn_interface_t::pins_t btn_pins = { A2, A3, A4, A5, A6 };
btn_interface_t buttons(btn_pins);
/* ----------------------------------- Funções ----------------------------------- */ 
void process_button_act(btn_interface_t::btn_action_t btn_act);
bool get_presence_sensor();
/* ----------------------------------- Rotinas ----------------------------------- */ 


void setup() {
  pinMode(PRESENCE_SENSOR_PIN, INPUT_PULLUP);
}

void loop() {

  switch (m_state) {
    case state_idle:
      {

        break;
      }
    case state_select_product:
      {
        btn_interface_t::btn_action_t btn_act = btn_interface_t::btn_action_t::NONE;
        btn_act = buttons.get_action();
        process_button_act(btn_act);
        break;
      }
    case state_moving_motor:
      {
        timer_t tim(30000);  // verifica qual coluna estamos para dar esse tempo
        while (!tim.timer_count_zero() || !get_presence_sensor()) {
          bool flag = false;
          if (flag == false) {
            flag = true;
            // mantem motor ligado
          }
        }
        // desliga motor
        m_state = state_verify_money;
        break;
      }
    case state_verify_money:
      {

        break;
      }
    default:
      {
        break;
      }
  }
}


void process_button_act(btn_interface_t::btn_action_t btn_act) {
  switch (btn_act) {
    case btn_interface_t::btn_action_t::LEFT:
      {

        break;
      }
    case btn_interface_t::btn_action_t::RIGHT:
      {

        break;
      }
    case btn_interface_t::btn_action_t::TOP:
      {

        break;
      }
    case btn_interface_t::btn_action_t::DOWN:
      {

        break;
      }
    case btn_interface_t::btn_action_t::CENTER:
      {

        break;
      }
    case btn_interface_t::btn_action_t::NONE:
      {

        break;
      }
  }
}


bool get_presence_sensor() {
  digitalRead(PRESENCE_SENSOR_PIN);
}
