#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include "page.h"

namespace fs = std::filesystem;

class Pager
{
public:
    Pager() { initialize("database.db"); }
    Pager(const char* filename) { initialize(filename); }
    ~Pager() { m_FileStream.close(); }

    bool Write(const Page& page, uint32_t pageid);
    bool Read(Page* page, uint32_t pageid);

    uint32_t GetDatabaseSize();
    uint32_t GetDatabasePageCount();

private:
    void initialize(const char* filename);
    fs::path m_DatabasePath;
    std::fstream m_FileStream;
};
