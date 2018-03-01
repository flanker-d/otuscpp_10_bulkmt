#include <file_logger.h>
#include <metricks.h>
#include <fstream>
#include <sstream>
#include <third_party/picosha2/picosha2.h>

file_logger::file_logger(int workers_count)
  : m_is_run(true)
  , m_workers_count(workers_count)
{
}

file_logger::~file_logger()
{
  //std::cout << "file queue: " << m_queue.size() << std::endl;
}

void file_logger::update(const cmd_block_t &cmd)
{
  std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
  m_queue.push(cmd);
  m_cv_queue.notify_one();
}

void file_logger::run()
{
  for(int i = 0; i < m_workers_count; i++)
  {
    std::string thread_name = "file" + std::to_string(i+1);
    metricks::instance().register_thread(thread_name);
    m_workers.emplace_back(std::thread(&file_logger::worker, this, thread_name));
  }
}

void file_logger::stop()
{
  m_is_run = false;
  m_cv_queue.notify_all();

  for(auto& wrkr : m_workers)
    wrkr.join();
}

void file_logger::worker(const std::string& thread_name)
{
  while(m_is_run || !m_queue.empty())
  {
    std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
    m_cv_queue.wait(lk, [&]() { return (!m_queue.empty() || !m_is_run); });
    if(!m_is_run && m_queue.empty()) return;

    auto cmd_pipeline = m_queue.front();
    m_queue.pop();
    lk.unlock();
#ifdef METRICS_EXTENDED
    sha256_calc(cmd_pipeline.block);
#endif
    write_to_file(cmd_pipeline, thread_name);

    metricks::instance().blocks_incr(thread_name);
    metricks::instance().commands_incr(thread_name, cmd_pipeline.count);
  }
}

void file_logger::sha256_calc(const std::string &cmd)
{
  for(int i = 0; i < 20; i++)
    picosha2::hash256_hex_string(cmd);
}

std::string file_logger::get_new_filename(const time_t &time, const std::string &thread_name, int seq_num)
{
  std::stringstream ss;
  ss << std::hex << std::this_thread::get_id();
  return "bulk" + std::to_string(time) + "_" + thread_name + "_" + std::to_string(seq_num) + "_" + ss.str() + ".log";
}

void file_logger::write_to_file(const cmd_block_t &cmd_block, const std::string &thread_name)
{
  std::ofstream output_file(get_new_filename(cmd_block.time, thread_name, cmd_block.block_seq_number));
  output_file << cmd_block.block << std::endl;
  output_file.flush();
  output_file.close();
}


