#include <console_logger.h>
#include <metricks.h>

console_logger::console_logger()
  : m_is_run(true)
{
  metricks::instance().register_thread(m_thread_name);
}

console_logger::~console_logger()
{
  //std::cout << "console queue: " << m_queue.size() << std::endl;
}

void console_logger::update(const cmd_block_t &cmd)
{
  std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
  m_queue.push(cmd);
  m_cv_queue.notify_one();
}

void console_logger::run()
{
  m_worker = std::thread(&console_logger::worker, this);
}

void console_logger::stop()
{
  m_is_run = false;
  m_cv_queue.notify_all();

  m_worker.join();
}

void console_logger::worker()
{
  while(m_is_run || !m_queue.empty())
  {
    std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
    m_cv_queue.wait(lk, [&]() { return (!m_queue.empty() || !m_is_run); });
    if(!m_is_run && m_queue.empty()) return;
    auto cmd_pipeline = m_queue.front();
    m_queue.pop();
    lk.unlock();

    std::cout << "bulk: " << cmd_pipeline.block << std::endl;

    metricks::instance().blocks_incr(m_thread_name);
    metricks::instance().commands_incr(m_thread_name, cmd_pipeline.count);
  }
}
