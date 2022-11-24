typedef struct
{    
    if ( 
        MetadataStream.Header.MaskValid.GenericParam == 1 &&
        MetadataStream.Header.NumOfRecords.GenericParamLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} GenericParamRid <read=rid>;
