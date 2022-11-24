typedef struct
{
    DWORD Token;
} ENC_MAP_RECORD;

typedef struct ( DWORD ENCMapLength )
{
    ENC_MAP_RECORD Records[ENCMapLength] <optimize=false>;
} ENC_MAP_TABLE;
