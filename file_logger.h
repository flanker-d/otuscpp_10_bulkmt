#pragma once 

#include <observer/observer.h>
#include <fstream>

class file_logger
    : public commands_observer
    , public time_observer
{
  public:
    void update_commands_observer(const std::string& cmd) override;
    void update_time_observer(const std::time_t& time) override;

  private:
    std::string get_new_filename();

  private:
    time_t m_time;
};
