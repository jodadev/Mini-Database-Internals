#pragma once

enum class Status
{
    Success,
    OutOfBounds,
    InvalidArgument,
    PageFull,
    FileNotOpen,
    IOError,
    Corruption
};
