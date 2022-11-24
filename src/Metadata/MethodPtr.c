typedef struct
{
    MethodRid Method;
} METHOD_PTR_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD methodPtrLen )
{
    METHOD_PTR_RECORD Records[methodPtrLen] <optimize=false>;
} METHOD_PTR_TABLE;
