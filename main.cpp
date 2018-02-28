#include <interpreter.h>

int main(int argc, char **argv)
{
  if (argc == 2)
  {
    std::unique_ptr<interpreter> ipr = std::make_unique<interpreter>(std::stoi(argv[1]));
    ipr->run();
  }

  return 0;
}