#include <console_logger.h>
#include <iostream>

console_logger::console_logger()
  : m_thread(&console_logger::worker, this)
{
}

void console_logger::update_commands_observer(const std::string& cmd)
{
  std::lock_guard<std::mutex> lk(m_cv_mutex);
  m_queue.push(cmd);
  m_cv.notify_one();
}

void console_logger::worker()
{
  while(true)
  {
    std::unique_lock<std::mutex> lk(m_cv_mutex);
    m_cv.wait(lk, [this](){ return m_queue.size(); });
    auto cmd = m_queue.front();
    m_queue.pop();
    lk.unlock();

    std::cout << "bulk: " << cmd << std::endl;
  }
}
