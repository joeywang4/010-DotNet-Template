local int HasFieldMarshalSize = 0;

typedef enum<BYTE> { Field_67, Param_67 } HasFieldMarshalTag;

typedef struct
{
    if ( HasFieldMarshalSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.Field == 1 && 
            MetadataStream.Header.NumOfRecords.FieldLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.FieldLength;
        if (
            MetadataStream.Header.MaskValid.Param == 1 && 
            MetadataStream.Header.NumOfRecords.ParamLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ParamLength;

        HasFieldMarshalSize = (maximum < (1 << 15)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( HasFieldMarshalSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            HasFieldMarshalTag table : 1;
            WORD index : 15;
        }
    }
    else
    {
        if ( ReadUInt() == 0 )
        {
            DWORD token <comment="null">;
        }
        else
        {
            HasFieldMarshalTag table : 1;
            DWORD index : 31;
        }
    }
    BitfieldEnablePadding();
} HasFieldMarshal;
