#include <metricks.h>
#include <algorithm>

metricks &metricks::instance()
{
  static metricks inst;
  return inst;
}

void metricks::register_thread(const std::string &thread_id)
{
  thread_metricks metr(thread_id);
  m_metricks.emplace(std::move(std::make_pair(thread_id, std::move(metr))));
}

void metricks::lines_incr(const std::string &thread_id)
{
  auto thr_metr = m_metricks.find(thread_id);
  if(thr_metr != m_metricks.end())
    *(thr_metr->second.lines.get()) += 1;
}

void metricks::blocks_incr(const std::string &thread_id)
{
  auto thr_metr = m_metricks.find(thread_id);
  if(thr_metr != m_metricks.end())
    *(thr_metr->second.blocks.get()) += 1;
}

void metricks::commands_incr(const std::string &thread_id, int commands)
{
  auto thr_metr = m_metricks.find(thread_id);
  if(thr_metr != m_metricks.end())
    *(thr_metr->second.commands.get()) += commands;
}

void metricks::print_metrics()
{
//  int total_blocks = 0;
//  int total_commands = 0;
  for(auto& metr : m_metricks)
  {
//    if((metr.first != "main") && (metr.first != "log"))
//    {
//      total_blocks += *(metr.second.blocks);
//      total_commands += *(metr.second.commands);
//    }

    if(metr.first == "main")
      std::cout << metr.first
                << ": lines: " << *(metr.second.lines)
                << ", blocks: " << *(metr.second.blocks)
                << ", commands: " << *(metr.second.commands)
                << std::endl;
    else
      std::cout << metr.first
                << ": blocks: " << *(metr.second.blocks)
                << ", commands: " << *(metr.second.commands)
                << std::endl;
  }

  //std::cout << "total_blocks_in_files: " << total_blocks << ", total_commands_in_files: " << total_commands << std::endl;
}
