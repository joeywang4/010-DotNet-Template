typedef struct
{
    DWORD OSPlatformId;
    DWORD OSMajorVersion;
    DWORD OSMinorVersion;
    AssemblyRefRid AssemblyRef;
} ASSEMBLY_REF_OS_RECORD;

typedef struct ( DWORD assemblyRefOSLength )
{
    ASSEMBLY_REF_OS_RECORD Records[assemblyRefOSLength] <optimize=false>;
} ASSEMBLY_REF_OS_TABLE;
