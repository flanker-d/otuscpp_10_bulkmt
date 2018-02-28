#include <commands_storage.h>

bool commands_storage_t::is_empty()
{
  return commands.empty();
}

std::size_t commands_storage_t::commands_count()
{
  return commands.size();
}

void commands_storage_t::clear()
{
  commands.clear();
}

void commands_storage_t::init_time()
{
  time = std::time(nullptr);
  commands.clear();
}

void commands_storage_t::append(const std::string &cmd)
{
  commands.push_back(cmd);
}

cmd_pipeline_t commands_storage_t::make_pipeline()
{
  cmd_pipeline_t pipeline;
  pipeline.time = time;
  for (const auto &cmd : commands)
  {
    if (pipeline.cmd_pipeline.empty())
    {
      pipeline.cmd_pipeline.append(cmd);
    }
    else
    {
      pipeline.cmd_pipeline.append(", " + cmd);
    }
  }
  return pipeline;
}
