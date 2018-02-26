#pragma once

#include <memory>
#include <vector>

class utils
{
  public:
    static std::string make_cmd_pipeline(const std::vector<std::string>& commands_pipeline);
};
