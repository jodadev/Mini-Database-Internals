#include <iostream>
#include "test.h"

//* PAGER
bool test_empty_database();
bool test_write_page_zero();
bool test_read_page();
bool test_overwrite_page();
bool test_multiple_pages();
bool test_invalid_read();
bool test_page_out_of_bounds();

//* RECORDS
bool test_get_record_count();
bool test_insert_record_to_page();
bool test_read_record_from_page();
bool test_invalid_record();
bool test_page_full();
bool test_write_record_page_to_disk();



int main()
{
    std::cout << "================ PAGER TESTS ================\n";
    RUN_TEST(test_empty_database);
    RUN_TEST(test_write_page_zero);
    RUN_TEST(test_read_page);
    RUN_TEST(test_overwrite_page);
    RUN_TEST(test_multiple_pages);
    RUN_TEST(test_invalid_read);
    RUN_TEST(test_page_out_of_bounds);

    std::cout << "================ RECORD TESTS ================\n";
    RUN_TEST(test_get_record_count);
    RUN_TEST(test_insert_record_to_page);
    RUN_TEST(test_read_record_from_page);
    RUN_TEST(test_invalid_record);
    RUN_TEST(test_page_full);
    RUN_TEST(test_write_record_page_to_disk);
}
