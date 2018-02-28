#pragma once

#include <observer.h>

class file_logger
  : public observer
{
  public:
    void update(const cmd_pipeline_t &cmd) override;

  private:
    std::string get_new_filename(const time_t &time);
};
