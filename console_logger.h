#pragma once

#include <observer.h>
#include <iostream>

class console_logger
  : public observer
{
  public:
    void update(const cmd_pipeline_t &cmd) override;
};
