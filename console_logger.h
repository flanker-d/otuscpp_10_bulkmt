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
    ~console_logger() override = default;

    void update(const cmd_pipeline_t &cmd) override;
    void run() override;
    void stop() override;

  private:
    void worker();

  private:
    std::condition_variable m_cv;
    std::mutex m_cv_mutex;
    std::queue<std::string> m_queue;
    std::atomic<bool> m_is_run;
    std::thread m_worker;
};
