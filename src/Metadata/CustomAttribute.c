typedef struct
{
    HasCustomAttribute Parent;
    CustomAttributeType Type;
    BLOB_OFFSET Value;
} CUSTOM_ATTRIBUTE_RECORD;

typedef struct ( DWORD customAttributeLen )
{
    CUSTOM_ATTRIBUTE_RECORD Records[customAttributeLen] <optimize=false>;
} CUSTOM_ATTRIBUTE_TABLE;
