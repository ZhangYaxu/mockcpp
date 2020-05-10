#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.
cmake -G "MSYS Makefiles" -DCMAKE_C_COMPILER=iccarm  -DCMAKE_CXX_COMPILER=iccarm
make

