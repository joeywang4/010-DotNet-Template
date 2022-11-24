typedef struct
{
    DWORD Offset;
    DWORD Flags;
    STRING_OFFSET Name;
    Implementation implementation;
} MANIFEST_RESOURCE_RECORD;

typedef struct ( DWORD manifestResourceLength )
{
    MANIFEST_RESOURCE_RECORD Records[manifestResourceLength] <optimize=false>;
} MANIFEST_RESOURCE_TABLE;
