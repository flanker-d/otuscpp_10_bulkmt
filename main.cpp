#include <interpreter.h>

int main(int argc, char **argv)
{
  if (argc == 2)
  {
    std::shared_ptr<interpreter> ipr = std::make_shared<interpreter>(std::stoi(argv[1]));
    ipr->run();
  }
  return 0;
}
