local int TypeOrMethodDefSize = 0;

typedef enum<BYTE> { TypeDef_76, Method_76 } TypeOrMethodDefTag;

typedef struct
{
    if ( TypeOrMethodDefSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.TypeDef == 1 &&
            MetadataStream.Header.NumOfRecords.TypeDefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (
            MetadataStream.Header.MaskValid.Method == 1 &&
            MetadataStream.Header.NumOfRecords.MethodLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MethodLength;

        TypeOrMethodDefSize = (maximum < (1 << 15)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( TypeOrMethodDefSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            MemberForwardedTag table : 1;
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
            MemberForwardedTag table : 1;
            DWORD index : 31;
        }
    }
    BitfieldEnablePadding();
} TypeOrMethodDef;
