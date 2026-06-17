#pragma once
#include <stdint.h>
#include "page.h"
#include "status.h"
#include "record.h"

class Records 
{
public:
    Records() = default;

    uint32_t GetRecordCount(const Page& page);

    Status InsertRecord(Page& page, const Record& record);

    Status ReadRecord(const Page& page, uint32_t recordID, Record* record);

};
