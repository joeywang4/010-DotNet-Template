typedef struct
{
    DWORD Token;
    DWORD FuncCode;
} ENC_LOG_RECORD;

typedef struct ( DWORD encLogLength )
{
    ENC_LOG_RECORD Records[encLogLength] <optimize=false>;
} ENC_LOG_TABLE;
