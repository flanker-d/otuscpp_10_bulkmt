#pragma once

#include <memory>

class interpreter;

class cmd_handler
{
  public:
    virtual void process_cmd(const std::string& cmd, const std::shared_ptr<interpreter>& ipr_ptr) = 0;
};
