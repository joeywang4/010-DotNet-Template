typedef struct
{    
    if ( 
        MetadataStream.Header.MaskValid.AssemblyRef == 1 &&
        MetadataStream.Header.NumOfRecords.AssemblyRefLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} AssemblyRefRid <read=rid>;
