typedef struct
{
    if (
        MetadataStream.Header.MaskValid.Field == 1 &&
        MetadataStream.Header.NumOfRecords.FieldLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} FieldRid <read=rid>;
