#include "test.h"
#include "records.h"
#include "pager.h"

bool test_get_record_count()
{
    Records records;

    // Manual insert data
    Page page;
    // Page header (record count: 1)
    page.data[0] = 0x02;
    // Record One: ID = 300
    page.data[4] = 0x2C;
    page.data[5] = 0x01;
    // Record One: Name = Ghost
    page.data[8] = 0x47;
    page.data[9] = 0x68;
    page.data[10] = 0x6F;
    page.data[11] = 0x73;
    page.data[12] = 0x74;
    // Record Two: ID = 5
    page.data[40] = 0x05;
    // Record Two: Name = Blank

    CHECK(records.GetRecordCount(page) == 2)

    return true;
}

bool test_insert_record_to_page()
{
    Records records;

    Page page;

    CHECK(records.InsertRecord(page, {44, "Hello World!"}) == Status::Success)

    return true;
}

bool test_read_record_from_page()
{
    Records records;

    // Manual insert data
    Page page;
    // Page header (record count: 1)
    page.data[0] = 0x01;
    // Record One: ID = 300
    page.data[4] = 0x2C;
    page.data[5] = 0x01;
    // Record One: Name = Ghost
    page.data[8] = 0x47;
    page.data[9] = 0x68;
    page.data[10] = 0x6F;
    page.data[11] = 0x73;
    page.data[12] = 0x74;

    Record record;
    CHECK(records.ReadRecord(page, 0, &record) == Status::Success)

    return true;
}

bool test_invalid_record()
{
    Records records;
    // Manual insert data
    Page page;
    records.InsertRecord( page, {300,"Hello World!"});
    Record record;
    CHECK(records.ReadRecord(page, 1, &record) == Status::OutOfBounds)

    return true;
}

bool test_page_full()
{
    Records records;
    // Manual insert data
    Page page;
    
    // Insert max recors
    for(size_t i = 0; i < 113; i++)
    {
        records.InsertRecord( page, {300,"Hello World!"});
    }

    CHECK(records.InsertRecord(page, {300,"Hello World!"}) == Status::PageFull)

    return true;
}

bool test_write_record_page_to_disk()
{
    std::filesystem::remove("test.bin");
    Pager pager("test.bin");
    Records records;
    Page page;
    Record record {
        54, 
        "Ghost"
    };
    Page newPage;
    Record newRecord;

    // Insert record in a Page and write to disk
    records.InsertRecord(page, record);
    pager.Write(page, 0);

    // Read page from disk and extract data from page to Record struct
    pager.Read(&newPage, 0);
    records.ReadRecord(newPage, 0, &newRecord);

    CHECK(record.id == 54 
        && record.name[0] == 'G'
        && record.name[1] == 'h'
        && record.name[2] == 'o'
        && record.name[3] == 's'
        && record.name[4] == 't'
    )

    return true;
}
