typedef struct
{
    DWORD OffSet;
    FieldRid Field;
} FIELD_LAYOUT_RECORD;

typedef struct ( DWORD fieldLayoutLength )
{
    FIELD_LAYOUT_RECORD Records[fieldLayoutLength] <optimize=false>;
} FIELD_LAYOUT_TABLE;
