typedef struct
{
    MethodDefOrRef Method;
    BLOB_OFFSET Instantiation;
} METHOD_SPEC_RECORD;

typedef struct ( DWORD methodSpecLength )
{
    METHOD_SPEC_RECORD Records[methodSpecLength] <optimize=false>;
} METHOD_SPEC_TABLE;
