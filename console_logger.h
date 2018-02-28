#pragma once

#include <observer.h>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <queue>

class console_logger
  : public observer
{
  public:
    console_logger();
    ~console_logger() override;

    void update(const cmd_block_t &cmd) override;
    void run() override;
    void stop() override;

  private:
    void worker();

  private:
    std::condition_variable m_cv_queue;
    std::mutex m_cv_queue_mutex;
    std::queue<cmd_block_t> m_queue;
    std::atomic<bool> m_is_run;
    std::thread m_worker;

    std::string m_thread_name = "log";
};
