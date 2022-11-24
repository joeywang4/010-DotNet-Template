typedef struct
{
    WORD Type;
    HasConstant Parent;
    BLOB_OFFSET Value;
} CONSTANT_RECORD;

typedef struct ( DWORD constantLen )
{
    CONSTANT_RECORD Records[constantLen] <optimize=false>;
} CONSTANT_TABLE;
