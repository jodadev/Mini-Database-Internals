#include "test.h"
#include <filesystem>
#include "pager.h"
#include "page.h"

bool test_empty_database()
{
    std::filesystem::remove("data/test.bin");

    Pager pager("test.bin");

    CHECK(pager.GetDatabasePageCount() == 0);

    return true;
}

bool test_write_page_zero()
{
    std::filesystem::remove("data/test.bin");

    Pager pager("test.bin");
    Page page;

    page.data[0] = 'H';

    CHECK(pager.Write(page, 0) == Status::Success)

    return true;
}

bool test_read_page()
{
    std::filesystem::remove("data/test.bin");

    Pager pager("test.bin");
    Page page;

    page.data[0] = 'H'; page.data[1] = 'i'; page.data[2] = '!';

    pager.Write(page, 0);

    Page data;
  
    CHECK(pager.Read(&data, 0) == Status::Success)

    return true;
}

bool test_overwrite_page()
{
    std::filesystem::remove("data/test.bin");

    Pager pager("test.bin");
    Page page;

    page.data[0] = 'H'; page.data[1] = 'i'; page.data[2] = '!';

    pager.Write(page, 0);   // append new page

    Page data;
    pager.Read(&data, 0);

    page.data[0] = 'B'; page.data[1] = 'i'; page.data[2] = 't';

    pager.Write(page, 0); // overwrite page 0

    pager.Read(&data, 0);
    CHECK(data.data[0] == 'B' && data.data[1] == 'i' && data.data[2] == 't');

    return true;
}

bool test_multiple_pages()
{
    std::filesystem::remove("data/test.bin");

    Pager pager("test.bin");
    Page page1; page1.data[0] = 'A';
    Page page2; page2.data[0] = 'B';
    Page page3; page3.data[0] = 'C';

    pager.Write(page1, 0);
    pager.Write(page2, 1);
    pager.Write(page3, 2);

    Page read1;
    Page read2;
    Page read3;

    pager.Read(&read1, 0);
    pager.Read(&read2, 1);
    pager.Read(&read3, 2);

    CHECK(read1.data[0] == 'A' && read2.data[0] == 'B' && read3.data[0] == 'C');

    return true;
}

bool test_invalid_read()
{
    std::filesystem::remove("data/test.bin");

    Pager pager("test.bin");
    Page page;

    pager.Write(page, 0);

    Page data;
    CHECK(pager.Read(&data, 99) != Status::Success);

    return true;
}

bool test_page_out_of_bounds()
{
    std::filesystem::remove("data/test.bin");

    Pager pager("test.bin");
    Page page;

    CHECK(pager.Write(page, 5) != Status::Success);

    return true;
}
