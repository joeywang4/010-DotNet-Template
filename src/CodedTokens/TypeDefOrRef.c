local int TypeDefOrRefSize = 0;

typedef enum<BYTE> { TypeDef_64, TypeRef_64, TypeSpec_64 } TypeDefOrRefTag;

typedef struct
{
    if ( TypeDefOrRefSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.TypeDef == 1 && 
            MetadataStream.Header.NumOfRecords.TypeDefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (
            MetadataStream.Header.MaskValid.TypeRef == 1 && 
            MetadataStream.Header.NumOfRecords.TypeRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;
        if (
            MetadataStream.Header.MaskValid.TypeSpec == 1 && 
            MetadataStream.Header.NumOfRecords.TypeSpecLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeSpecLength;

        TypeDefOrRefSize = (maximum < (1 << 14)) ? 2 : 4;
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
            TypeDefOrRefTag table : 2;
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
            TypeDefOrRefTag table : 2;
            DWORD index : 30;
        }
    }
    BitfieldEnablePadding();
} TypeDefOrRef;
