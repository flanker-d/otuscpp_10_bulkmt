#pragma once

#include <ctime>
#include <string>

struct cmd_block_t
{
  time_t time;
  std::string block;
  int count;
};

class observer
{
  public:
    virtual void update(const cmd_block_t &cmd) = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual ~observer() = default;
};
