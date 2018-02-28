#include <console_logger.h>

console_logger::console_logger()
  : m_is_run(true)
{
}

void console_logger::update(const cmd_pipeline_t &cmd)
{
  std::unique_lock<std::mutex> lk(m_cv_mutex);
  m_queue.push(cmd.cmd_pipeline);
  m_cv.notify_one();
}

void console_logger::run()
{
  m_worker = std::thread(&console_logger::worker, this);
}

void console_logger::stop()
{
  m_is_run = false;
  m_cv.notify_all();
  m_worker.join();
}

void console_logger::worker()
{
  while(m_is_run)
  {
    std::unique_lock<std::mutex> lk(m_cv_mutex);
    m_cv.wait(lk, [&]() { return (!m_queue.empty() || !m_is_run); });
    if(!m_is_run) return;
    auto cmd_pipeline = m_queue.front();
    m_queue.pop();
    lk.unlock();

    std::cout << "bulk: " << cmd_pipeline << std::endl;
  }
}
