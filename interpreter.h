#pragma once

#include <file_logger.h>
#include <console_logger.h>
#include <commands_storage.h>
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

  private:
    void subscribe(std::shared_ptr<observer> obs);

    void process_open_brace();

    void process_close_brace();

    void process_simple_cmd(const std::string &cmd);

    void notify();

  private:
    std::size_t m_block_size;
    std::shared_ptr<console_logger> m_console_logger;
    std::shared_ptr<file_logger> m_file_logger;
    std::vector<std::shared_ptr<observer>> m_subs;
    int m_open_braces_count = 0;
    commands_storage_t m_commands_storage;
};
