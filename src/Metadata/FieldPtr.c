typedef struct
{
    FieldRid Field;
} FIELD_PTR_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD fieldPtrLen )
{
    FIELD_PTR_RECORD Records[fieldPtrLen] <optimize=false>;
} FIELD_PTR_TABLE;
