# Mini DB Internals

A C++ project for learning database storage internals from the ground up.

## Current Status

### v0.1 Pager
- Fixed-size 4096-byte pages
- Zero-based page IDs
- Binary file-backed storage
- Page count calculation
- Append, overwrite, and bounds validation
- Basic pager tests