#pragma once

class timer_t {
public:
  timer_t(unsigned long interval) : m_interval(m_interval), m_prev_time(0) {}

  bool timer_count_zero() {
    unsigned long now_time = millis(); 
    
    if (now_time - m_prev_time >= m_interval) {
      m_prev_time = now_time;
      return true; 
    }
    
    return false;
  }

private:
  unsigned long m_interval; 
  unsigned long m_prev_time;
};