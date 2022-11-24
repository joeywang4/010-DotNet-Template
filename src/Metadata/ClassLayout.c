typedef struct
{
    WORD PackingSize;
    DWORD ClassSize;
    TypeDefRid Parent;
} CLASS_LAYOUT_RECORD;

typedef struct ( DWORD classLayoutLength )
{
    CLASS_LAYOUT_RECORD Records[classLayoutLength] <optimize=false>;
} CLASS_LAYOUT_TABLE;
