#include "records.h"

constexpr uint32_t RECORD_SIZE = 36;
constexpr uint32_t HEADER_SIZE = 4;

#include <bit>
#include <array>

template <typename T>
static std::array<unsigned char, sizeof(T)> to_bytes(const T& obj) 
{
    return std::bit_cast<std::array<unsigned char, sizeof(T)>>(obj);
}   


uint32_t Records::GetRecordCount(const Page& page)
{
    uint32_t value = 0;
    int32_t multiplier = -8;

    for(size_t i = 0; i < 4; i++)
        value |= static_cast<uint8_t>(page.data[i]) << (multiplier += 8);

    return value;
}

Status Records::InsertRecord(Page& page, const Record& record)
{
    // Check if page has enough size
    uint32_t count = GetRecordCount(page);
    uint32_t max = (PAGE_SIZE -  HEADER_SIZE) / RECORD_SIZE;
    if (count >= max) return Status::PageFull;

    // Convert Record obj to raw bytes
    auto bytes = to_bytes(record);                              // record as array of bytes
    uint32_t byte_index = 0;                                    // address to track bytes array
    uint32_t pageAddr = HEADER_SIZE + (count * RECORD_SIZE);    // address in page data

    // Add record data to page - append
    for(size_t addr = pageAddr; addr < (pageAddr + RECORD_SIZE); addr++)
        page.data[addr] = bytes[byte_index++];

    // increment count and add to the page header
    count++;
    int32_t shift = -8;
    for(size_t addr = 0; addr < HEADER_SIZE; addr++)
        page.data[addr] = (count >> (shift += 8)) & 0xFF;
    
    return Status::Success;
}

Status Records::ReadRecord(const Page& page, uint32_t recordID, Record* rec)
{
    // HEADER_SIZE + RECORD_SIZE * recordID
    if (!rec) return Status::InvalidArgument;
    if (recordID >= GetRecordCount(page)) return Status::OutOfBounds;
    uint32_t addr = (RECORD_SIZE * recordID) + HEADER_SIZE;

    // Read Record ID (4bytes)
    rec->id = 0;
    int32_t byte = -8;
    for(size_t i = 0; i < 4; i++)
        rec->id |= (page.data[addr++] << (byte += 8)); 
    // std::cout << "ID: " << rec.id << "\n";

    // Read Record Name (32bytes)
    for(size_t i = 0; i < 32; i++)
    {
        rec->name[i] = page.data[addr++];
    }
    // std::cout << "ID: " << rec.name << "\n";

    return Status::Success;
}
