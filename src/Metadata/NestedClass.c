typedef struct
{
    TypeDefRid NestedClass;
    TypeDefRid EnclosingClass;
} NESTED_CLASS_RECORD;

typedef struct ( DWORD nestedClassLength )
{
    NESTED_CLASS_RECORD Records[nestedClassLength] <optimize=false>;
} NESTED_CLASS_TABLE;
