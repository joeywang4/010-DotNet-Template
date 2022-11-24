local int ResolutionScopeSize = 0;

typedef enum<BYTE> { Module_75, ModuleRef_75, AssemblyRef_75, TypeRef_75 } ResolutionScopeTag;

typedef struct
{
    if ( ResolutionScopeSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.Module == 1 && 
            MetadataStream.Header.NumOfRecords.ModuleLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ModuleLength;
        if (
            MetadataStream.Header.MaskValid.ModuleRef == 1 && 
            MetadataStream.Header.NumOfRecords.ModuleRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ModuleRefLength;
        if (
            MetadataStream.Header.MaskValid.AssemblyRef == 1 && 
            MetadataStream.Header.NumOfRecords.AssemblyRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.AssemblyRefLength;
        if (
            MetadataStream.Header.MaskValid.TypeRef == 1 && 
            MetadataStream.Header.NumOfRecords.TypeRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;

        ResolutionScopeSize = (maximum < (1 << 14)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( ResolutionScopeSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="current assembly">;
        }
        else if ( ReadUShort() == 1 )
        {
            WORD token <comment="same module">;
        }
        else
        {
            ResolutionScopeTag table : 2;
            WORD index : 14;
        }
    }
    else
    {
        if ( ReadUInt() == 0 )
        {
            DWORD token <comment="current assembly">;
        }
        else if ( ReadUInt() == 1 )
        {
            DWORD token <comment="same module">;
        }
        else
        {
            ResolutionScopeTag table : 2;
            DWORD index : 30;
        }
    }
    BitfieldEnablePadding();
} ResolutionScope;
