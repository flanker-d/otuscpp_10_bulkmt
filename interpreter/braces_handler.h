#pragma once

#include <interpreter/interpreter.h>

class braces_handler
    : public cmd_handler
{
  public:
    void process_cmd(const std::string& cmd, const std::shared_ptr<interpreter>& ipr_ptr) override;

  private:
    std::vector<std::string> m_commands_pipeline;
    int m_open_braces_count = 1;
};
