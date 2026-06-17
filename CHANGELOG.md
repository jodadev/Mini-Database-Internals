# Changelog

## Version 0.2

### Additions
- `status.h` an enum which will help when debugging system level issues. Meant to act as a return value for functions.
- `record.h` holds the structure for what a `Record` object should be: `id(int32)` and `name[32]`
- `records.h/cpp` handles inserting, reading and getting record count from a `Page`.
- `test_records.cpp` tests the new `Records` and `Record`(struct) logic for writing/reading data from a `Page`.

### Change
- `Page::data` is now type `uint8_t` rather than `char`. This required changes to the pager file I/O - the data needed to be reinterpreted from `uint8_t` to `char`.
- removed the macros CHECK and RUN_TEST from cpp files to new file - `test.h` 
- `test_pager` now returns new `Status` for Write/Read functions.

## Version 0.1
Version 0.1 consists of 

### Additions
- `page.h struct:` raw data structure for making pages which has only a array of type char the size of 4096 bytes.
- `pager.h/cpp:` main file for reading/writing data and uses the page struct for raw data structure.
- `/tests`
    - created a test pager file to test certain things like overwrite, multiple pages, invalid read/append, et.
