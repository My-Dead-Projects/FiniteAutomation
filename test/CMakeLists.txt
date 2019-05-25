add_executable(Test test.cpp )

target_link_libraries(Test DFA)
add_test(NAME Test COMMAND Test)
