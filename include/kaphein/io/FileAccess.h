#ifndef KAPHEIN_HGRD_kaphein_io_FileAccess_h
#define KAPHEIN_HGRD_kaphein_io_FileAccess_h

enum kaphein_io_FileAccess
{
    kaphein_io_FileAccess_none = 0x00
    , kaphein_io_FileAccess_read = 0x01
    , kaphein_io_FileAccess_write = 0x02
    , kaphein_io_FileAccess_readAndWrite = kaphein_io_FileAccess_read | kaphein_io_FileAccess_write
};

#endif
