#pragma once

#include <ctime>
#include <string>

struct cmd_pipeline_t
{
  time_t time;
  std::string cmd_pipeline;
};

class observer
{
  public:
    virtual void update(const cmd_pipeline_t &cmd) = 0;
};
