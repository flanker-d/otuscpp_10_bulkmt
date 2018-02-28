#pragma once

#include <vector>
#include <ctime>
#include <observer.h>

struct commands_storage_t
{
  time_t time;
  std::vector<std::string> commands;

  bool is_empty();

  std::size_t commands_count();

  void clear();

  void init_time();

  void append(const std::string &cmd);

  cmd_pipeline_t make_pipeline();
};