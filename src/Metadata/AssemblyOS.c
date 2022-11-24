typedef struct
{
    DWORD OSPlatformId;
    DWORD OSMajorVersion;
    DWORD OSMinorVersion;
} ASSEMBLY_OS_RECORD;

typedef struct ( DWORD assemblyOSLength )
{
    ASSEMBLY_OS_RECORD Records[assemblyOSLength] <optimize=false>;
} ASSEMBLY_OS_TABLE;
