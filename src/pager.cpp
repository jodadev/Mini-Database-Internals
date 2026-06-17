#include "pager.h"
#include <exception>


void Pager::initialize(const char* filename)
{
    fs::path dataDir = fs::current_path() / "data";

    if (!fs::is_directory(dataDir)) // No directory found, create it
    {
        fs::create_directory(dataDir);
    }

    m_DatabasePath = (dataDir / filename).lexically_normal();
    
    m_FileStream.open(m_DatabasePath, std::ios_base::binary | std::ios_base::in | std::ios_base::out);
    
    if (!m_FileStream)
    {
        std::ofstream create(m_DatabasePath, std::ios::binary);
        create.close();

        m_FileStream.open(
            m_DatabasePath,
            std::ios::in |
            std::ios::out |
            std::ios::binary
        );
    }
    
}

Status Pager::Write(const Page& page, uint32_t pageid)
{
    if (!m_FileStream.is_open()) return Status::FileNotOpen;

    uint32_t pageCount = GetDatabasePageCount();

    if (pageid > pageCount)  return Status::OutOfBounds;

    if (pageid == pageCount)  // append a new page
    {
        m_FileStream.seekp(0, m_FileStream.end);
        m_FileStream.write(reinterpret_cast<const char*>(page.data), PAGE_SIZE);
    }
    else                                    // overwrite a page 
    {
        m_FileStream.seekp(PAGE_SIZE * pageid, m_FileStream.beg);
        m_FileStream.write(reinterpret_cast<const char*>(page.data), PAGE_SIZE);
    }

    m_FileStream.seekp(0, m_FileStream.beg);

    return m_FileStream.good() ? Status::Success : Status::IOError;

}

Status Pager::Read(Page* page, uint32_t pageid)
{
    if (!page) return Status::InvalidArgument;
    if (!m_FileStream.is_open()) return Status::FileNotOpen;
    if (pageid >= GetDatabasePageCount()) return Status::OutOfBounds;
    
    m_FileStream.seekg(PAGE_SIZE * pageid, m_FileStream.beg);
    m_FileStream.read(reinterpret_cast<char*>(page->data), PAGE_SIZE);
    m_FileStream.seekg(0, m_FileStream.beg);

    return m_FileStream.good() ? Status::Success : Status::IOError;
   
}

uint32_t Pager::GetDatabaseSize()
{
    m_FileStream.seekg(0, m_FileStream.end);
    int size = m_FileStream.tellg();
    m_FileStream.seekg(0, m_FileStream.beg);

    return (uint32_t)size;
}

uint32_t Pager::GetDatabasePageCount()
{
    uint32_t sizeInBytes = GetDatabaseSize();

    if (sizeInBytes % PAGE_SIZE != 0)
    {
        throw std::runtime_error("File size is corrupt!");
    }

    return sizeInBytes / PAGE_SIZE;
}
