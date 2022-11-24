typedef struct
{
    BLOB_OFFSET Signature;
} TYPE_SPEC_RECORD;

typedef struct ( DWORD typeSpecLength )
{
    TYPE_SPEC_RECORD Records[typeSpecLength] <optimize=false>;
} TYPE_SPEC_TABLE;
