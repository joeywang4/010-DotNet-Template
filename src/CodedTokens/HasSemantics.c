local int HasSemanticsSize = 0;

typedef enum<BYTE> { Event_70, Property_70 } HasSemanticsTag;

typedef struct
{
    if ( HasSemanticsSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.Event == 1 && 
            MetadataStream.Header.NumOfRecords.EventLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.EventLength;
        if (
            MetadataStream.Header.MaskValid.Property == 1 && 
            MetadataStream.Header.NumOfRecords.PropertyLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.PropertyLength;

        HasSemanticsSize = (maximum < (1 << 15)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( HasSemanticsSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            HasSemanticsTag table : 1;
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
            HasSemanticsTag table : 1;
            DWORD index : 31;
        }
    }
    BitfieldEnablePadding();
} HasSemantics;
