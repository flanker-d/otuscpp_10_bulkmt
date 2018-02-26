#include <bulk.h>
#include <iostream>

bulk::bulk(int block_size)
  : m_interpreter(std::make_shared<interpreter>(block_size))
  , m_file_logger(std::make_shared<file_logger>())
  , m_console_logger(std::make_shared<console_logger>())
{
  m_interpreter->attach_commands_observer(m_file_logger);
  m_interpreter->attach_time_observer(m_file_logger);
  m_interpreter->attach_commands_observer(m_console_logger);
}

void bulk::run()
{
  std::string command;
  while(std::getline(std::cin, command))
  {
    m_interpreter->process_cmd(command);
  }
}
