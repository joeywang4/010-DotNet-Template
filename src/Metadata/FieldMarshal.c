typedef struct
{
    HasFieldMarshal Parent;
    BLOB_OFFSET NativeType;
} FIELD_MARSHAL_RECORD;

typedef struct ( DWORD fieldMarshalLength )
{
    FIELD_MARSHAL_RECORD Records[fieldMarshalLength] <optimize=false>;
} FIELD_MARSHAL_TABLE;
