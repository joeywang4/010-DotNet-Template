typedef struct
{    
    if (
        MetadataStream.Header.MaskValid.Event == 1 &&
        MetadataStream.Header.NumOfRecords.EventLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} EventRid <read=rid>;
