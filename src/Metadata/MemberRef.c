typedef struct
{
    MemberRefParent Class;
    STRING_OFFSET Name;
    BLOB_OFFSET Signature;
} MEMBER_REF_RECORD;

typedef struct ( DWORD memberRefLen )
{
    MEMBER_REF_RECORD Records[memberRefLen] <optimize=false>;
} MEMBER_REF_TABLE;
