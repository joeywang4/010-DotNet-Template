typedef struct
{
    WORD MajorVersion;
    WORD MinorVersion;
    WORD BuildNumber;
    WORD RevisionNumber;
    DWORD Flags;
    BLOB_OFFSET PublicKeyOrToken;
    STRING_OFFSET Name;
    STRING_OFFSET Locale;
    BLOB_OFFSET HashValue;
} ASSEMBLY_REF_RECORD;

typedef struct ( DWORD assemblyRefLength )
{
    ASSEMBLY_REF_RECORD Records[assemblyRefLength] <optimize=false>;
} ASSEMBLY_REF_TABLE;
