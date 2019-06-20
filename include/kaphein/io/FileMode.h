#ifndef KAPHEIN_HGRD_kaphein_io_FileMode_h
#define KAPHEIN_HGRD_kaphein_io_FileMode_h

enum kaphein_io_FileMode
{
    kaphein_io_FileMode_open = 0
    , kaphein_io_FileMode_openOrCreate
    , kaphein_io_FileMode_createNew
    , kaphein_io_FileMode_create
    , kaphein_io_FileMode_truncate
    , kaphein_io_FileMode_append
};

#endif
