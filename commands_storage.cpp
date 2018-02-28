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

cmd_block_t commands_storage_t::make_block(int seq_num)
{
  cmd_block_t cmd_block;
  cmd_block.time = time;
  cmd_block.count = commands.size();
  cmd_block.block_seq_number = seq_num;

  for (const auto &cmd : commands)
  {
    if (cmd_block.block.empty())
    {
      cmd_block.block.append(cmd);
    }
    else
    {
      cmd_block.block.append(", " + cmd);
    }
  }
  return cmd_block;
}
