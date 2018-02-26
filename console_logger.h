#pragma once

#include <observer/observer.h>
#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>

class console_logger
    : public commands_observer
{
  public:
    console_logger();
    void update_commands_observer(const std::string& cmd) override;
  private:
    void worker();
  private:
    std::thread m_thread;
    std::condition_variable m_cv;
    std::mutex m_cv_mutex;
    std::queue<std::string> m_queue;
};
