typedef struct
{
    WORD MappingFlags;
    MemberForwarded memberForwarded;
    STRING_OFFSET ImportName;
    ModuleRefRid ImportScope;
} IMPL_MAP_RECORD;

typedef struct ( DWORD implMapLength )
{
    IMPL_MAP_RECORD Records[implMapLength] <optimize=false>;
} IMPL_MAP_TABLE;
