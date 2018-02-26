#pragma once

#include <memory>
#include <observer/subject.h>

class commands_observer
    : public std::enable_shared_from_this<commands_observer>
{
  public:
    virtual void update_commands_observer(const std::string& cmd) = 0;
};

class time_observer
    : public std::enable_shared_from_this<time_observer>
{
  public:
    virtual void update_time_observer(const std::time_t& time) = 0;
};
