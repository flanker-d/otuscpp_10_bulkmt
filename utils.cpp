#include <utils.h>

std::string utils::make_cmd_pipeline(const std::vector<std::string>& commands_pipeline)
{
  std::string cmd_pipeline;
  for(const std::string& cmd : commands_pipeline)
  {
    if(cmd_pipeline.size() == 0)
      cmd_pipeline.append(cmd);
    else
      cmd_pipeline.append(", " + cmd);
  }
  return cmd_pipeline;
}
