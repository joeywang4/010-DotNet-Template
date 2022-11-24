typedef struct
{    
    if (
        MetadataStream.Header.MaskValid.ModuleRef == 1 &&
        MetadataStream.Header.NumOfRecords.ModuleRefLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} ModuleRefRid <read=rid>;
