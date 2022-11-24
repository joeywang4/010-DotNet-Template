local int MemberForwardedSize = 0;

typedef enum<BYTE> { Field_72, Method_72 } MemberForwardedTag;

typedef struct
{
    if ( MemberForwardedSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.Field == 1 && 
            MetadataStream.Header.NumOfRecords.FieldLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.FieldLength;
        if (
            MetadataStream.Header.MaskValid.Method == 1 && 
            MetadataStream.Header.NumOfRecords.MethodLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MethodLength;

        MemberForwardedSize = (maximum < (1 << 15)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( MemberForwardedSize == 2 )
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
} MemberForwarded;
