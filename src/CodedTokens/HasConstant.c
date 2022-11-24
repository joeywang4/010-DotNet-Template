local int HasConstantSize = 0;

typedef enum<BYTE> { Field_65, Param_65, Property_65 } HasConstantTag;

typedef struct
{
    if ( HasConstantSize == 0 )
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
        if (
            MetadataStream.Header.MaskValid.Property == 1 && 
            MetadataStream.Header.NumOfRecords.PropertyLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.PropertyLength;

        HasConstantSize = (maximum < (1 << 14)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( TypeDefOrRefSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            HasConstantTag table : 2;
            WORD index : 14;
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
            HasConstantTag table : 2;
            DWORD index : 30;
        }
    }
    BitfieldEnablePadding();
} HasConstant;
