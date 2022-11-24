typedef struct
{
    WORD Number;
    WORD Flags;
    TypeOrMethodDef Owner;
    STRING_OFFSET Name;
} GENERIC_PARAM_RECORD;

typedef struct ( DWORD genericParamLength )
{
    GENERIC_PARAM_RECORD Records[genericParamLength] <optimize=false>;
} GENERIC_PARAM_TABLE;
