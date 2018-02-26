#pragma once

#include <interpreter/interpreter.h>

class simple_cmd_handler
    : public cmd_handler
{
  public:
    void process_cmd(const std::string& cmd, const std::shared_ptr<interpreter>& ipr_ptr) override;
  private:
    std::vector<std::string> m_commands_pipeline;
};
