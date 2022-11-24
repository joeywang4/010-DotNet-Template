typedef struct
{
    DWORD HashAlgId;
    WORD MajorVersion;
    WORD MinorVersion;
    WORD BuildNumber;
    WORD RevisionNumber;
    DWORD Flags;
    BLOB_OFFSET PublicKey;
    STRING_OFFSET Name;
    STRING_OFFSET Locale;
} ASSEMBLY_RECORD;

typedef struct ( DWORD assemblyLength )
{
    ASSEMBLY_RECORD Records[assemblyLength] <optimize=false>;
} ASSEMBLY_TABLE;
