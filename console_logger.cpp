#include <console_logger.h>

void console_logger::update(const cmd_pipeline_t &cmd)
{
  std::cout << "bulk: " << cmd.cmd_pipeline << std::endl;
}
