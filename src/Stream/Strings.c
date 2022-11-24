typedef struct
{
    BYTE str[ReadStringLength(FTell())];
} GENERIC_STRING <read=(str)>;

typedef struct
{
    FSeek(FTell() + 1); // skip the first null byte

    local int nextLen;
    for (nextLen = ReadStringLength(FTell()); nextLen > 1; nextLen = ReadStringLength(FTell()))
    {
        GENERIC_STRING str;
    }
} STRING_HEAP;
