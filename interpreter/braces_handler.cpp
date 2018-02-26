#include <interpreter/braces_handler.h>
#include <interpreter/simple_cmd_handler.h>
#include <utils.h>

void braces_handler::process_cmd(const std::string& cmd, const std::shared_ptr<interpreter>& ipr_ptr)
{
  if(cmd == "{")
  {
    m_open_braces_count++;
  }
  else if(cmd == "}")
  {
    m_open_braces_count--;
  }
  else
  {
    m_commands_pipeline.push_back(cmd);
  }

  if(m_open_braces_count == 0)
  {
    ipr_ptr->notify_commands_observers(utils::make_cmd_pipeline(m_commands_pipeline));
    ipr_ptr->change_state(std::make_shared<simple_cmd_handler>());
    m_commands_pipeline.clear();
    m_open_braces_count = 0;
  }
}
