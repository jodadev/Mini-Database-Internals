#pragma once
#include <filesystem>
#include <fstream>
#include <stdint.h>
#include "page.h"
#include "status.h"

namespace fs = std::filesystem;

class Pager
{
public:
    Pager() { initialize("database.bin"); }
    Pager(const char* filename) { initialize(filename); }
    ~Pager() { m_FileStream.close(); }

    Status Write(const Page& page, uint32_t pageid);
    Status Read(Page* page, uint32_t pageid);

    uint32_t GetDatabaseSize();
    uint32_t GetDatabasePageCount();

private:
    void initialize(const char* filename);
    fs::path m_DatabasePath;
    std::fstream m_FileStream;
};
