typedef struct
{
    DWORD Flags;
    STRING_OFFSET Name;
    BLOB_OFFSET HashValue;
} FILE_RECORD;

typedef struct ( DWORD fileLength )
{
    FILE_RECORD Records[fileLength] <optimize=false>;
} FILE_TABLE;
