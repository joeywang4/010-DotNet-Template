typedef struct
{
    TypeDefRid Class;
    MethodDefOrRef MethodBody;
    MethodDefOrRef MethodDeclaration;
} METHOD_IMPL_RECORD;

typedef struct ( DWORD methodImplLength )
{
    METHOD_IMPL_RECORD Records[methodImplLength] <optimize=false>;
} METHOD_IMPL_TABLE;
