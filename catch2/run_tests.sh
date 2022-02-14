#!/bin/bash
lcov --zerocounters --directory build

./build/test/test_myapp

lcov --capture --directory build/ --output-file build/coverage.info
lcov --remove build/coverage.info '/usr/*' '*/extern/*' --output-file build/coverage.info
lcov --list build/coverage.info

genhtml build/coverage.info --output-directory build/coverage_report/ --function-coverage --branch-coverage --legend --demangle-cpp --num-spaces 4
