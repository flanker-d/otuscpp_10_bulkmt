#pragma once

#include <atomic>
#include <thread>
#include <map>
#include <iostream>

struct thread_metricks
{
  std::string thread_id;
  std::shared_ptr<std::atomic<int>> lines = std::make_shared<std::atomic<int>>(0);
  std::shared_ptr<std::atomic<int>> blocks = std::make_shared<std::atomic<int>>(0);
  std::shared_ptr<std::atomic<int>> commands = std::make_shared<std::atomic<int>>(0);

  thread_metricks(const std::string& thr_id)
    : thread_id(thr_id)
  {
  }
};

class metricks
{
  public:
    static metricks& instance();
    void register_thread(const std::string& thread_id);
    const int get_lines_count(const std::string &thread_id) const
    {
      auto thr_metr = m_metricks.find(thread_id);
      if(thr_metr != m_metricks.end())
        return *(thr_metr->second.lines.get());
    }
    void lines_incr(const std::string &thread_id);
    void blocks_incr(const std::string &thread_id);
    void commands_incr(const std::string &thread_id, int commands);
    void print_metrics();
  private:
    metricks() = default;
    metricks(const metricks& root) = delete;
    metricks& operator=(const metricks&) = delete;

  private:
    std::map<std::string, thread_metricks> m_metricks;
};