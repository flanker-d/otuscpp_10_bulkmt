#pragma once

#include <observer.h>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <queue>

class file_logger
  : public observer
{
  public:
    file_logger(int workers_count);
    ~file_logger() override = default;
    void update(const cmd_block_t &cmd) override;
    void run() override;
    void stop() override;

  private:
    void worker(const std::string& thread_name);
    std::string get_new_filename(const time_t &time);
    void write_to_file(const cmd_block_t& cmd_block);

  private:
    std::condition_variable m_cv;
    std::mutex m_cv_mutex;
    std::queue<cmd_block_t> m_queue;
    std::atomic<bool> m_is_run;
    std::vector<std::thread> m_workers;
    int m_workers_count = 1;
};
