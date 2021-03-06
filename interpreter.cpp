#include <interpreter.h>

using namespace std::chrono_literals;


interpreter::interpreter(int block_size)
  : m_block_size(block_size)
{
  metricks::instance().register_thread(m_thread_name);
  subscribe(std::make_shared<console_logger>());
  subscribe(std::make_shared<file_logger>(file_loggers_count));
}

void interpreter::run()
{
  run_observers();

#ifdef METRICS_EXTENDED
  auto ms_start = metricks::instance().get_time_now();
#endif

  std::string command;// = "123";
  while (std::getline(std::cin, command))
  //for(int i = 0; i < 3; i++)
  {
    metricks::instance().lines_incr(m_thread_name);
    process_cmd(command);
  }
  forced_dump();

  stop_observers();

#ifdef METRICS_EXTENDED
  auto res_time = metricks::instance().get_diff_time_now(ms_start);
#endif

  metricks::instance().print_metrics();

#ifdef METRICS_EXTENDED
  metricks::instance().print_time(res_time);
#endif
}

void interpreter::process_cmd(const std::string &cmd)
{
  if (cmd == "{")
  {
    process_open_bracket();
  }
  else if (cmd == "}")
  {
    process_close_bracket();
  }
  else
  {
    process_simple_cmd(cmd);
  }
}

void interpreter::forced_dump()
{
  if (m_open_brackets_count == 0)
  {
    notify();
  }
}

void interpreter::run_observers()
{
  for(auto& obs : m_subs)
    obs->run();
}

void interpreter::stop_observers()
{
  for(auto& obs : m_subs)
    obs->stop();
}

void interpreter::subscribe(std::shared_ptr<observer>&& obs)
{
  m_subs.emplace_back(std::move(obs));
}

void interpreter::process_open_bracket()
{
  m_open_brackets_count++;
  if (m_open_brackets_count == 1)
  {
    notify();
    m_commands_storage.init_time();
  }
}

void interpreter::process_close_bracket()
{
  m_open_brackets_count--;
  if (m_open_brackets_count == 0)
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
  if ((m_open_brackets_count == 0) && (m_commands_storage.commands_count() == m_block_size))
  {
    notify();
  }
}

void interpreter::notify()
{
  if (!m_commands_storage.is_empty())
  {
    cmd_block_t cmd = m_commands_storage.make_block(metricks::instance().get_blocks_count(m_thread_name));
    for (auto &s : m_subs)
    {
      s->update(cmd);
    }
    metricks::instance().blocks_incr(m_thread_name);
    metricks::instance().commands_incr(m_thread_name, cmd.count);
    m_commands_storage.clear();
  }
}
