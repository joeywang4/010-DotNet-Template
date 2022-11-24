typedef struct
{    
    if (
        MetadataStream.Header.MaskValid.Property == 1 &&
        MetadataStream.Header.NumOfRecords.PropertyLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} PropertyRid <read=rid>;
