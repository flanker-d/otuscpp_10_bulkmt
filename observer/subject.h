#pragma once

#include <memory>
#include <ctime>
#include <observer/observer.h>

class commands_observer;
class time_observer;

class commands_subject
{
  public:
    virtual void attach_commands_observer(const std::shared_ptr<commands_observer>& obs) = 0;
    virtual void notify_commands_observers(const std::string& commands_pipeline) = 0;
};

class time_subject
{
  public:
    virtual void attach_time_observer(const std::shared_ptr<time_observer>& obs) = 0;
    virtual void notify_time_observers(const std::time_t& time) = 0;
};
