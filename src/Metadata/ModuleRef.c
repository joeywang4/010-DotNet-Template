typedef struct
{
    STRING_OFFSET Name;
} MODULE_REF_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD moduleRefLength )
{
    MODULE_REF_RECORD Records[moduleRefLength] <optimize=false>;
} MODULE_REF_TABLE;
