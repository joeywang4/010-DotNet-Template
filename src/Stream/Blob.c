typedef struct (int headerSize)
{
    ENCODED_LEN length(headerSize);
    local int decodedLen = DecodeLength(length);
    BYTE data[decodedLen] <fgcolor=cDkPurple>;
} BLOB_DATA;

typedef struct
{
    FSeek(FTell() + 1); // skip the first null byte

    local int _headerSize;
    for ( _headerSize = GetCompressedLen(); _headerSize != 0; _headerSize = GetCompressedLen())
    {
        BLOB_DATA data(_headerSize);
    }
} BLOB_HEAP;
