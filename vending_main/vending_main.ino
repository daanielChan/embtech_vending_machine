/* ----------------------------------- Inclusões ----------------------------------- */
#include "button_interface.h"
#include "timer.h"
#include "led_matrix.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "motor.h"

/* ----------------------------------- Configurações ----------------------------------- */
constexpr uint32_t tempo_colunas_s[5] = { 30000, 30000, 30000, 30000, 30000 };
constexpr uint32_t custo_coluns_rs[5] = { 5, 10, 15, 20, 25 };



/* ----------------------------------- Variaveis e Classes ----------------------------------- */
using namespace driver;

constexpr int PRESENCE_SENSOR_PIN = A7;

/* --- LCD --- */
constexpr int LCD_ADDR = 0x27;
constexpr int LCD_COLUMNS = 20;
constexpr int LCD_ROWS = 4;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLUMNS, LCD_ROWS);

/* --- Botões --- */
constexpr btn_interface_t::pins_t BTN_PINS = { A2, A4, A3, A5, A6 };
btn_interface_t buttons(BTN_PINS);

/* --- Leds --- */
constexpr uint8_t LEDS_ROW_PINS[8] = { 8, 9, 10, 11, 12, 13, A0, A1 };
constexpr uint8_t LEDS_COLS_PINS[5] = { 2, 3, 4, 5, 6 };
led_matrix_t leds(LEDS_ROW_PINS, LEDS_COLS_PINS);

led_matrix_t::led_state_t led_state = { 0 };


/* --- Motores --- */
motor_t motores;

/* --- Sistema --- */
typedef enum {
  state_idle = 0,
  state_select_product,
  state_moving_motor,
  state_verify_money
} states_e;
states_e m_state = state_idle;

/* ----------------------------------- Funções ----------------------------------- */
void process_button_act(btn_interface_t::btn_action_t btn_act);
bool get_presence_sensor();
void update_display_coast();
/* ----------------------------------- Rotinas ----------------------------------- */


void setup() {
  pinMode(PRESENCE_SENSOR_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  update_display_coast();
}

void loop() {

  switch (m_state) {
    case state_idle:
      {
        m_state = state_select_product;
        break;
      }
    case state_select_product:
      {
        process_button_act(buttons.get_action());
        break;
      }
    case state_moving_motor:
      {
        timer_t tim(tempo_colunas_s[led_state.col]);  // verifica qual coluna estamos para dar esse tempo
        while (!tim.timer_count_zero() || !get_presence_sensor()) {
          bool flag = false;
          if (flag == false) {
            flag = true;
            motores.set_level(get_pin_num(), true);
          }
        }
        motores.set_level(get_pin_num(), false);
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
  if (btn_act != btn_interface_t::btn_action_t::NONE && btn_act != btn_interface_t::btn_action_t::CENTER) {
    led_state.state = false;
    leds.set_led(led_state);
  }

  switch (btn_act) {
    case btn_interface_t::btn_action_t::LEFT:
      {
        if (led_state.col == 4) {
          led_state.col = 0;
        } else {
          led_state.col++;
        }

        update_display_coast();

        break;
      }
    case btn_interface_t::btn_action_t::RIGHT:
      {
        if (led_state.col == 0) {
          led_state.col = 4;
        } else {
          led_state.col--;
        }

        update_display_coast();
        break;
      }
    case btn_interface_t::btn_action_t::TOP:
      {
        if (led_state.row == 0) {
          led_state.row = 7;
        } else {
          led_state.row--;
        }
        break;
      }
    case btn_interface_t::btn_action_t::DOWN:
      {
        if (led_state.row == 7) {
          led_state.row = 0;
        } else {
          led_state.row++;
        }
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

  led_state.state = true;
  leds.set_led(led_state);
}

bool get_presence_sensor() {
  digitalRead(PRESENCE_SENSOR_PIN);
}

void update_display_coast() {
  char buffer[8];

  sprintf(buffer, "%02d,00", custo_coluns_rs[led_state.col]);

  lcd.setCursor(1, 3);
  lcd.print("Valor: ");

  lcd.setCursor(8, 3);
  lcd.print(buffer);

  lcd.setCursor(14, 3);
  lcd.print("Reais");
}

int get_pin_num() {
    int ret_val = 0;

    int row = led_state.row;
    int col = led_state.col;

    if (row >= 0 && row < 8 && col >= 0 && col < 5) {
        ret_val = (row * 5) + col;
    } else {
        ret_val = -1;
    }
    return ret_val;
}

/* 
- Lógica Moedeiro e Noteiro.
- Lógica para gerenciar dinheiro que temos.
*/