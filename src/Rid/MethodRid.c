typedef struct
{
    if (
        MetadataStream.Header.MaskValid.Method == 1 &&
        MetadataStream.Header.NumOfRecords.MethodLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} MethodRid <read=rid>;
