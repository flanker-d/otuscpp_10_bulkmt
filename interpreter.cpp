#include <interpreter.h>

interpreter::interpreter(int block_size)
  : m_block_size(block_size)
  , m_console_logger(std::make_shared<console_logger>())
  , m_file_logger(std::make_shared<file_logger>())
{
  subscribe(m_console_logger);
  subscribe(m_file_logger);
}

void interpreter::run()
{
  std::string command;
  while (std::getline(std::cin, command))
  {
    process_cmd(command);
  }
}

void interpreter::process_cmd(const std::string &cmd)
{
  if (cmd == "{")
  {
    process_open_brace();
  }
  else if (cmd == "}")
  {
    process_close_brace();
  }
  else
  {
    process_simple_cmd(cmd);
  }
}

void interpreter::subscribe(std::shared_ptr<observer> obs)
{
  m_subs.push_back(obs);
}

void interpreter::process_open_brace()
{
  m_open_braces_count++;
  if (m_open_braces_count == 1)
  {
    notify();
    m_commands_storage.init_time();
  }
}

void interpreter::process_close_brace()
{
  m_open_braces_count--;
  if (m_open_braces_count == 0)
  {
    notify();
  }
}

void interpreter::process_simple_cmd(const std::string &cmd)
{
  if (m_commands_storage.commands_count() == 0)
  {
    m_commands_storage.init_time();
  }

  m_commands_storage.append(cmd);
  if ((m_open_braces_count == 0) && (m_commands_storage.commands_count() == m_block_size))
  {
    notify();
  }
}

void interpreter::notify()
{
  if (!m_commands_storage.is_empty())
  {
    cmd_pipeline_t cmd = m_commands_storage.make_pipeline();
    for (auto &s : m_subs)
    {
      s->update(cmd);
    }
    m_commands_storage.clear();
  }
}
