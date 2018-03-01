#pragma once

#include <file_logger.h>
#include <console_logger.h>
#include <commands_storage.h>
#include <metricks.h>
#include <memory>
#include <vector>
#include <iostream>

const int file_loggers_count = 2;

class interpreter
{
  public:
    interpreter(int block_size);
    void run();
    void process_cmd(const std::string &cmd);
    void run_observers();
    void stop_observers();

  private:
    void subscribe(std::shared_ptr<observer>&& obs);
    void process_open_bracket();
    void process_close_bracket();
    void process_simple_cmd(const std::string &cmd);
    void notify();

  private:
    std::size_t m_block_size;
    std::vector<std::shared_ptr<observer>> m_subs;
    int m_open_brackets_count = 0;
    commands_storage_t m_commands_storage;

    std::string m_thread_name = "main";
};
