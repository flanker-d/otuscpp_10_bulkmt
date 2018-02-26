#include <interpreter/simple_cmd_handler.h>
#include <interpreter/braces_handler.h>
#include <utils.h>

void simple_cmd_handler::process_cmd(const std::string& cmd, const std::shared_ptr<interpreter>& ipr_ptr)
{
  if(cmd == "{")
  {
    if(m_commands_pipeline.size() > 0)
      ipr_ptr->notify_commands_observers(utils::make_cmd_pipeline(m_commands_pipeline));

    ipr_ptr->change_state(std::make_shared<braces_handler>());
    ipr_ptr->notify_time_observers(std::time(nullptr));
  }
  else
  {
    if(m_commands_pipeline.size() == 0)
      ipr_ptr->notify_time_observers(std::time(nullptr));

    m_commands_pipeline.push_back(cmd);
    if(m_commands_pipeline.size() == ipr_ptr->block_size())
    {
      ipr_ptr->notify_commands_observers(utils::make_cmd_pipeline(m_commands_pipeline));
      m_commands_pipeline.clear();
    }
  }
}
