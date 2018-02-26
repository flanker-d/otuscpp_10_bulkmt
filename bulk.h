#pragma once

#include <interpreter/interpreter.h>
#include <file_logger.h>
#include <console_logger.h>

class bulk
{
  public:
    bulk(int block_size);

    void run();

  private:
    std::shared_ptr<interpreter> m_interpreter;
    std::shared_ptr<file_logger> m_file_logger;
    std::shared_ptr<console_logger> m_console_logger;
};
