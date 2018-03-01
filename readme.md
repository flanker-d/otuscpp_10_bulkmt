BulkMT

[![Build Status](https://travis-ci.org/flanker-d/otuscpp_10_bulkmt.svg?branch=master)](https://travis-ci.org/flanker-d/otuscpp_10_bulkmt)

*Тестовая среда:*
CPU: Intel® Core™ i7-6700 CPU @ 3.40GHz × 8 
RAM: 7.7 ГиБ
ОС: Ubuntu 16.04 LTS
Компилятор: gcc version 5.4.1 20160904

*Методика измерений:*
0. Подготовка к измерениям

- Задаётся число потоков, которые будут писать в файл: 
`const int file_loggers_count = 8192;`
- Выполняется компиляция программы (release, без опримизации)
- при помощи команды `./stress_test.sh | ./bulk
mt 3` запускается скрипт: 
`#!/bin/bash
for (( i=1; i <= 99999; i++ ))
do
echo "cmd$i"
done`

Далее начинает выполняться поток программы, в основном цикле которого реализована следующая последовательность действий: 

1. Запускаем потоки log, file1..fileN
2. Засекаем время начала измерений
3. Выполняем чтение данных из stdin, формируем блоки команд, отправляем в потоки log, file1..fileN 
4. Останавливаем потоки log, file1..fileN
5. Ждём завершения потоков, когда они закончат записывать данные в файл
6. Засекаем время конца измерений, вычисляем время выполнения алгоритма 

В прогграммном коде измерения выглядят так:

`void interpreter::run()
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

  stop_observers();

#ifdef METRICS_EXTENDED
  auto res_time = metricks::instance().get_diff_time_now(ms_start);
#endif

  metricks::instance().print_metrics();

#ifdef METRICS_EXTENDED
  metricks::instance().print_time(res_time);
#endif
}`

*Операции при записи в файл:*
Перед записью в файл, поток выполняет вычисление sha256.
`#ifdef METRICS_EXTENDED
    sha256_calc(cmd_pipeline.block);
#endif
    write_to_file(cmd_pipeline, thread_name);`

Для загрузки ядер CPU на 90-100% вычисление sha256 повторяется 100 раз.
`void file_logger::sha256_calc(const std::string &cmd)
{
  for(int i = 0; i < 100; i++)
    picosha2::hash256_hex_string(cmd);
}`

*Результаты тестирования:*
![table](https://github.com/flanker-d/otuscpp_10_bulkmt/blob/pics/pics/table.jpg)
![diagram](https://github.com/flanker-d/otuscpp_10_bulkmt/blob/pics/pics/diagram.jpg)

*Вывод:*
- N потоков быстрее справляются с задачей, чем 1 поток
- Линейное увеличение числа потоков не ведёт к линейному росту производительности, в начале график похож на функцию y=1/x
- При увеличении числа потоков до 8192 снижается производительность программы уменьшается, скорее всего это связано с переключением 8 потоков CPU между 8192 потоками программы

