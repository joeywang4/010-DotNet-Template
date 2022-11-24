typedef struct
{
    ResolutionScope _ResolutionScope;
    STRING_OFFSET    Name;
    STRING_OFFSET    Namespace;
} TYPE_REF_RECORD <comment=GetFullName(Namespace, Name)>;

typedef struct ( DWORD typeRefLen )
{
    TYPE_REF_RECORD Records[typeRefLen] <optimize=false>;
} TYPE_REF_TABLE;
