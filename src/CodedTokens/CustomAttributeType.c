local int CustomAttributeTypeSize = 0;

typedef enum<BYTE> { 
    TypeRef_74, 
    TypeDef_74, 
    Method_74, 
    MemberRef_74, 
    String_74 
} CustomAttributeTypeTag;

typedef struct
{
    if ( CustomAttributeTypeSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.TypeRef == 1 && 
            MetadataStream.Header.NumOfRecords.TypeRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;
        if (
            MetadataStream.Header.MaskValid.TypeDef == 1 && 
            MetadataStream.Header.NumOfRecords.TypeDefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (
            MetadataStream.Header.MaskValid.Method == 1 && 
            MetadataStream.Header.NumOfRecords.MethodLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (
            MetadataStream.Header.MaskValid.MemberRef == 1 && 
            MetadataStream.Header.NumOfRecords.MemberRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MemberRefLength;
        // if (MetadataStream.Header.MaskValid.String == 1 && MetadataStream.Header.NumOfRecords.StringLength > maximum) maximum = MetadataStream.Header.NumOfRecords.StringLength; // TODO: there is no String md table

        CustomAttributeTypeSize = (maximum < (1 << 13)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( CustomAttributeTypeSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            CustomAttributeTypeTag table : 3;
            WORD index : 13;
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
            CustomAttributeTypeTag table : 3;
            DWORD index : 29;
        }
    }
    BitfieldEnablePadding();
} CustomAttributeType;
