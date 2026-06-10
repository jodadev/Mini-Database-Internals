#pragma once
#include <stdint.h>

constexpr uint32_t PAGE_SIZE = 4096;

struct Page
{
    char data[PAGE_SIZE]; 
    Page()
    {
        // Clear garbage
        for(size_t i= 0; i < PAGE_SIZE; i++)
        {
            data[i] = 0;
        }
    }
};
