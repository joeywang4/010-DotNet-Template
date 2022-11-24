local int MethodDefOrRefSize = 0;

typedef enum<BYTE> { Method_71, MemberRef_71 } MethodDefOrRefTag;

typedef struct
{
    if ( MethodDefOrRefSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.Method == 1 && 
            MetadataStream.Header.NumOfRecords.MethodLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (
            MetadataStream.Header.MaskValid.MemberRef == 1 && 
            MetadataStream.Header.NumOfRecords.MemberRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MemberRefLength;

        MethodDefOrRefSize = (maximum < (1 << 15)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( MethodDefOrRefSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            MethodDefOrRefTag table : 1;
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
            MethodDefOrRefTag table : 1;
            DWORD index : 31;
        }
    }
    BitfieldEnablePadding();
} MethodDefOrRef;
