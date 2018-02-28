#include <file_logger.h>
#include <fstream>
#include <sstream>

file_logger::file_logger(int workers_count)
  : m_is_run(true)
  , m_workers_count(workers_count)
{
}

void file_logger::update(const cmd_pipeline_t &cmd)
{
  std::unique_lock<std::mutex> lk(m_cv_mutex);
  m_queue.push(cmd);
  m_cv.notify_one();
}

void file_logger::run()
{
  for(int i = 0; i < m_workers_count; i++)
    m_workers.emplace_back(std::thread(&file_logger::worker, this));
}

void file_logger::stop()
{
  m_is_run = false;
  m_cv.notify_all();
  for(auto& wrkr : m_workers)
    wrkr.join();
}

void file_logger::worker()
{
  while(m_is_run)
  {
    std::unique_lock<std::mutex> lk(m_cv_mutex);
    m_cv.wait(lk, [&]() { return (!m_queue.empty() || !m_is_run); });
    if(!m_is_run) return;
    auto cmd_pipeline = m_queue.front();
    m_queue.pop();
    lk.unlock();

    write_to_file(cmd_pipeline);
  }
}

std::string file_logger::get_new_filename(const time_t &time)
{
  std::stringstream ss;
  ss << std::hex << std::this_thread::get_id();
  return "bulk" + std::to_string(time) + "_" + ss.str() + ".log";
}

void file_logger::write_to_file(const cmd_pipeline_t &cmd_pipeline)
{
  std::ofstream output_file(get_new_filename(cmd_pipeline.time));
  output_file << cmd_pipeline.cmd_pipeline << std::endl;
  output_file.flush();
  output_file.close();
}


