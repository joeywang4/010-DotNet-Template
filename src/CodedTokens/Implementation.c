local int ImplementationSize = 0;

typedef enum<BYTE> { File_73, AssemblyRef_73, ExportedType_73 } ImplementationTag;

typedef struct
{
    if ( ImplementationSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.File == 1 && 
            MetadataStream.Header.NumOfRecords.FileLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.FileLength;
        if (
            MetadataStream.Header.MaskValid.AssemblyRef == 1 && 
            MetadataStream.Header.NumOfRecords.AssemblyRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.AssemblyRefLength;
        if (
            MetadataStream.Header.MaskValid.ExportedType == 1 && 
            MetadataStream.Header.NumOfRecords.ExportedTypeLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ExportedTypeLength;

        ImplementationSize = (maximum < (1 << 14)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( ImplementationSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            ImplementationTag table : 2;
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
            ImplementationTag table : 2;
            DWORD index : 30;
        }
    }
    BitfieldEnablePadding();
} Implementation;
