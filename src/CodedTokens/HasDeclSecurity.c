local int HasDeclSecuritySize = 0;

typedef enum<BYTE> { TypeDef_68, Method_68, Assembly_68 } HasDeclSecurityTag;

typedef struct
{
    if ( HasDeclSecuritySize == 0 )
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
        if (
            MetadataStream.Header.MaskValid.Assembly == 1 && 
            MetadataStream.Header.NumOfRecords.AssemblyLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.AssemblyLength;

        HasDeclSecuritySize = (maximum < (1 << 14)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( HasDeclSecuritySize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            HasDeclSecurityTag table : 2;
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
            HasDeclSecurityTag table : 2;
            DWORD index : 30;
        }
    }
    BitfieldEnablePadding();
} HasDeclSecurity;
