#pragma once

#define CHECK(cond)     \
    if (!(cond)) return false;

#define RUN_TEST(test)      \
    std::cout << (test() ? "[PASS] " : "[FAIL] ")  \
        << #test            \
        << "\n";