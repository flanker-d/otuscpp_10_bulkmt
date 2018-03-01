#pragma once

#include <observer.h>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <queue>
#include <iostream>

class file_logger
  : public observer
{
  public:
    file_logger(int workers_count);
    ~file_logger() override;
    void update(const cmd_block_t &cmd) override;
    void run() override;
    void stop() override;

  private:
    void worker(const std::string& thread_name);
    void sha256_calc(const std::string &cmd);
    std::string get_new_filename(const time_t &time, const std::string &thread_name, int seq_num);
    void write_to_file(const cmd_block_t& cmd_block, const std::string &thread_name);

  private:
    std::condition_variable m_cv_queue;
    std::mutex m_cv_queue_mutex;
    std::queue<cmd_block_t> m_queue;
    std::atomic<bool> m_is_run;
    std::vector<std::thread> m_workers;
    int m_workers_count = 1;
};
