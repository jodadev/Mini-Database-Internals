# Mini DB Internals

A C++(20) project for learning database storage internals from the ground up.

## Current Status

### v0.1 Pager
- Fixed-size 4096-byte pages
- Zero-based page IDs
- Binary file-backed storage
- Page count calculation
- Append, overwrite, and bounds validation
- Basic pager tests

### v0.2 Record
- Fixed-size records (uint32_t id, char name[32])
- Page header with record_count
- Record count serialization/deserialization
- Record insertion into page memory
- Record retrieval by index
- Record offset calculation (HEADER_SIZE + RECORD_SIZE * index)
- Bounds validation for record access
- Shared status/result system
- Page-level record layout abstraction
- Record serialization to raw bytes
- Record unit tests
- Pager + Records integration tests
