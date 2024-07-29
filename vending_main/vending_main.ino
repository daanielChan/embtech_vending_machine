typedef enum {
  state_idle = 0,
  state_select_product,
  state_moving_motor,
  state_verify_money
} states_e;

states_e m_state;

void setup() {


}

void loop() {
  switch (m_state) {
    case state_idle:
    {

      break;
    }
    case state_select_product:
    {

      break;
    }
    case state_moving_motor:
    {

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