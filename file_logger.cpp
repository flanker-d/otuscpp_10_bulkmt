#include <file_logger.h>
#include <fstream>

void file_logger::update(const cmd_pipeline_t &cmd)
{
  std::ofstream output_file(get_new_filename(cmd.time));
  output_file << cmd.cmd_pipeline << std::endl;
  output_file.flush();
  output_file.close();
}

std::string file_logger::get_new_filename(const time_t &time)
{
  return "bulk" + std::to_string(time) + ".log";
}
