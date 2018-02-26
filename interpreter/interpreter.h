#pragma once 

#include <observer/subject.h>
#include <interpreter/cmd_handler.h>
#include <vector>

class interpreter
    : public commands_subject
    , public time_subject
    , public std::enable_shared_from_this<interpreter>
{
  public:
    interpreter(int block_size);
    void process_cmd(const std::string& cmd);

    void change_state(const std::shared_ptr<cmd_handler>& state_handler);
    const int& block_size() const;

    void attach_commands_observer(const std::shared_ptr<commands_observer>& obs) override;
    void notify_commands_observers(const std::string& commands_pipeline) override;
    void attach_time_observer(const std::shared_ptr<time_observer>& obs) override;
    void notify_time_observers(const std::time_t& time) override;

  private:
    void append_cmd(const std::string& cmd);

  private:
    int m_block_size;
    std::shared_ptr<cmd_handler> m_cmd_handler;
    std::vector<std::shared_ptr<commands_observer>> m_cmd_observers;
    std::vector<std::shared_ptr<time_observer>> m_time_observers;
};
