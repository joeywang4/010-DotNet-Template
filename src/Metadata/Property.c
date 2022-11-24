typedef struct
{
    WORD PropFlags;
    STRING_OFFSET Name;
    BLOB_OFFSET Type;
} PROPERTY_RECORD;

typedef struct ( DWORD propertyLength )
{
    PROPERTY_RECORD Records[propertyLength] <optimize=false>;
} PROPERTY_TABLE;
