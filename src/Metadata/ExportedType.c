typedef struct
{
    DWORD Flags;
    DWORD TypeDefId;
    STRING_OFFSET TypeName;
    STRING_OFFSET TypeNamespace;
    Implementation implementation;
} EXPORTED_TYPE_RECORD;

typedef struct ( DWORD exportedTypeLength )
{
    EXPORTED_TYPE_RECORD Records[exportedTypeLength] <optimize=false>;
} EXPORTED_TYPE_TABLE;
