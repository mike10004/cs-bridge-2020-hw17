#!/bin/bash

exec valgrind --tool=memcheck --leak-check=full --track-origins=yes --gen-suppressions=all --leak-resolution=med --vgdb=no tests/cmake-build/hw17_tests

