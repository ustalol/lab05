# CMake generated Testfile for 
# Source directory: /home/lol/lab05/banking
# Build directory: /home/lol/lab05/banking/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(banking_tests "/home/lol/lab05/banking/build/banking_tests")
set_tests_properties(banking_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/lol/lab05/banking/CMakeLists.txt;47;add_test;/home/lol/lab05/banking/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
