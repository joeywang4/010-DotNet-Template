typedef struct
{    
    if (
        MetadataStream.Header.MaskValid.Param == 1 &&
        MetadataStream.Header.NumOfRecords.ParamLength > 0x10000
    )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} ParamRid <read=rid>;
