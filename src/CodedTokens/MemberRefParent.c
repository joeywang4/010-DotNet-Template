local int MemberRefParentSize = 0;

typedef enum<BYTE> { TypeDef_69, TypeRef_69, ModuleRef_69, Method_69, TypeSpec_69 } MemberRefParentTag;

typedef struct
{
    if ( MemberRefParentSize == 0)
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
            MetadataStream.Header.MaskValid.ModuleRef == 1 && 
            MetadataStream.Header.NumOfRecords.ModuleRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ModuleRefLength;
        if (
            MetadataStream.Header.MaskValid.Method == 1 && 
            MetadataStream.Header.NumOfRecords.MethodLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (
            MetadataStream.Header.MaskValid.TypeSpec == 1 && 
            MetadataStream.Header.NumOfRecords.TypeSpecLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeSpecLength;

        MemberRefParentSize = (maximum <  (1 << 13)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( MemberRefParentSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            MemberRefParentTag table : 3;
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
            MemberRefParentTag table : 3;
            DWORD index : 29;
        }
    }
    BitfieldEnablePadding();
} MemberRefParent;
