local int HasCustomAttributeSize = 0;

typedef enum<BYTE> { 
    Method_66, Field_66, TypeRef_66, TypeDef_66, Param_66, 
    InterfaceImpl_66, MemberRef_66, Module_66, DeclSecurity_66, Property_66, 
    Event_66, StandAloneSig_66, ModuleRef_66, TypeSpec_66, Assembly_66,
    AssemblyRef_66, File_66, ExportedType_66, ManifestResource_66
} HasCustomAttributeTag;

typedef struct
{
    if ( HasCustomAttributeSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (
            MetadataStream.Header.MaskValid.Method == 1 && 
            MetadataStream.Header.NumOfRecords.MethodLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (
            MetadataStream.Header.MaskValid.Field == 1 && 
            MetadataStream.Header.NumOfRecords.FieldLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.FieldLength;
        if (
            MetadataStream.Header.MaskValid.TypeRef == 1 && 
            MetadataStream.Header.NumOfRecords.TypeRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;
        if (
            MetadataStream.Header.MaskValid.TypeDef == 1 && 
            MetadataStream.Header.NumOfRecords.TypeDefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (
            MetadataStream.Header.MaskValid.Param == 1 && 
            MetadataStream.Header.NumOfRecords.ParamLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ParamLength;

        if (
            MetadataStream.Header.MaskValid.InterfaceImpl == 1 && 
            MetadataStream.Header.NumOfRecords.InterfaceImplLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.InterfaceImplLength;
        if (
            MetadataStream.Header.MaskValid.MemberRef == 1 && 
            MetadataStream.Header.NumOfRecords.MemberRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.MemberRefLength;
        if (
            MetadataStream.Header.MaskValid.Module == 1 && 
            MetadataStream.Header.NumOfRecords.ModuleLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ModuleLength;
        if (
            MetadataStream.Header.MaskValid.DeclSecurity == 1 && 
            MetadataStream.Header.NumOfRecords.DeclSecurityLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.DeclSecurityLength;
        if (
            MetadataStream.Header.MaskValid.Property == 1 && 
            MetadataStream.Header.NumOfRecords.PropertyLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.PropertyLength;

        if (
            MetadataStream.Header.MaskValid.Event == 1 && 
            MetadataStream.Header.NumOfRecords.EventLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.EventLength;
        if (
            MetadataStream.Header.MaskValid.StandAloneSig == 1 && 
            MetadataStream.Header.NumOfRecords.StandAloneSigLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.StandAloneSigLength;
        if (
            MetadataStream.Header.MaskValid.ModuleRef == 1 && 
            MetadataStream.Header.NumOfRecords.ModuleRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ModuleRefLength;
        if (
            MetadataStream.Header.MaskValid.TypeSpec == 1 && 
            MetadataStream.Header.NumOfRecords.TypeSpecLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.TypeSpecLength;
        if (
            MetadataStream.Header.MaskValid.Assembly == 1 && 
            MetadataStream.Header.NumOfRecords.AssemblyLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.AssemblyLength;

        if (
            MetadataStream.Header.MaskValid.AssemblyRef == 1 && 
            MetadataStream.Header.NumOfRecords.AssemblyRefLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.AssemblyRefLength;
        if (
            MetadataStream.Header.MaskValid.File == 1 && 
            MetadataStream.Header.NumOfRecords.FileLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.FileLength;
        if (
            MetadataStream.Header.MaskValid.ExportedType == 1 && 
            MetadataStream.Header.NumOfRecords.ExportedTypeLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ExportedTypeLength;
        if (
            MetadataStream.Header.MaskValid.ManifestResource == 1 && 
            MetadataStream.Header.NumOfRecords.ManifestResourceLength > maximum
        ) maximum = MetadataStream.Header.NumOfRecords.ManifestResourceLength;

        HasCustomAttributeSize = (maximum < (1 << 11)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( HasCustomAttributeSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            HasCustomAttributeTag table : 5;
            WORD index : 11;
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
            HasCustomAttributeTag table : 5;
            DWORD index : 27;
        }
    }
    BitfieldEnablePadding();
} HasCustomAttribute;
