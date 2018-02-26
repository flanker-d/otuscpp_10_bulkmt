#include <file_logger.h>
#include <iostream>

void file_logger::update_commands_observer(const std::string& cmd)
{
  std::ofstream m_output_file(get_new_filename());
  m_output_file << cmd << std::endl;
  m_output_file.flush();
  m_output_file.close();
}

void file_logger::update_time_observer(const time_t& time)
{
  m_time = time;
}

std::string file_logger::get_new_filename()
{
  return "bulk" + std::to_string(m_time) + ".log";
}
