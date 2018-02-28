#pragma once

#include <observer.h>

class file_logger
  : public observer
{
  public:
    ~file_logger() override = default;
    void update(const cmd_pipeline_t &cmd) override;
    void run() override
    {

    }
    void stop() override
    {

    }

  private:
    std::string get_new_filename(const time_t &time);
};
