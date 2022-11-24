typedef struct
{
    if (
        MetadataStream.Header.MaskValid.TypeDef == 1 &&
        MetadataStream.Header.NumOfRecords.TypeDefLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} TypeDefRid <read=rid>;
