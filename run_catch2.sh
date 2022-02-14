#!/bin/bash
lcov --zerocounters --directory build

./build/test/catch2/test_catch2

lcov --capture --directory build/ --output-file build/coverage.info >/dev/null
lcov --remove build/coverage.info '/usr/*' '*/extern/*' --output-file build/coverage.info >/dev/null
lcov --list build/coverage.info

genhtml build/coverage.info --output-directory build/coverage_report/ --function-coverage --branch-coverage --legend --demangle-cpp --num-spaces 4 >/dev/null
