typedef struct
{
    DWORD RVA;
    FieldRid Field;
} FIELD_RVA_RECORD;

typedef struct ( DWORD fieldRVALength )
{
    FIELD_RVA_RECORD Records[fieldRVALength] <optimize=false>;
} FIELD_RVA_TABLE;
