cmake_minimum_required(VERSION 3.2)

project(bulkmt VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories (${PROJECT_SOURCE_DIR})

configure_file(version.h.in version.h)

add_executable(bulkmt
    bulk.cpp
    console_logger.cpp
    file_logger.cpp
    utils.cpp
    main.cpp
    interpreter/interpreter.cpp
    interpreter/cmd_handler.cpp
    interpreter/braces_handler.cpp
    interpreter/simple_cmd_handler.cpp
    observer/observer.cpp
    observer/subject.cpp)
target_link_libraries(bulkmt -lpthread)

set_target_properties(bulkmt PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

install(TARGETS bulkmt
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artyom.sorokoumov@gmail.com)

include(CPack)
