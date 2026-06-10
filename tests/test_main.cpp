#include <iostream>

bool test_empty_database();
bool test_write_page_zero();
bool test_read_page();
bool test_overwrite_page();
bool test_multiple_pages();
bool test_invalid_read();
bool test_invalid_append();

#define RUN_TEST(test)      \
    std::cout << (test() ? "[PASS] " : "[FAIL] ")  \
        << #test            \
        << "\n";

int main()
{
    RUN_TEST(test_empty_database);
    RUN_TEST(test_write_page_zero);
    RUN_TEST(test_read_page);
    RUN_TEST(test_overwrite_page);
    RUN_TEST(test_multiple_pages);
    RUN_TEST(test_invalid_read);
    RUN_TEST(test_invalid_append);
}
