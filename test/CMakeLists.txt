include_directories(../src)

add_executable(
    unit_tests
    ../src/desafio1.c
    tests_desafio1.c
    )

add_test(
  NAME
    unit
  COMMAND
    unit_tests
  )
