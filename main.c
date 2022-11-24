/**** .NET-SPECIFIC STRUCTURES ****/

// book keeping variables
local int64 StringHeapLoc;
local DWORD StringHeapSize;
local int64 GUIDLoc;
local DWORD GUIDSize;
local int64 BlobLoc;
local DWORD BlobSize;
local int64 USLoc;
local DWORD USSize;

// coded token tag size
local int TypeDefOrRefSize = 0;
local int HasConstantSize = 0;
local int HasCustomAttributeSize = 0;
local int HasFieldMarshalSize = 0;
local int HasDeclSecuritySize = 0;
local int MemberRefParentSize = 0;
local int HasSemanticsSize = 0;
local int MethodDefOrRefSize = 0;
local int MemberForwardedSize = 0;
local int ImplementationSize = 0;
local int CustomAttributeTypeSize = 0;
local int ResolutionScopeSize = 0;
local int TypeOrMethodDefSize = 0;

// .NET --- Offset Types

typedef struct
{
    if ( MetadataStream.Header.HeapOffsetSizes.StringSize )
    {
        DWORD offset <comment=Str("File offset: 0x%X", GetStringRAW(this))>;
    }
    else
    {
        WORD offset <comment=Str("File offset: 0x%X", GetStringRAW(this))>;
    }
} STRING_OFFSET <read=(offset),comment=CommentStringOffset>;

typedef struct
{
    if ( MetadataStream.Header.HeapOffsetSizes.BlobSize )
    {
        DWORD offset <comment=Str("File offset: 0x%X", GetBlobRAW(this))>;
    }
    else
    {
        WORD offset <comment=Str("File offset: 0x%X", GetBlobRAW(this))>;
    }
} BLOB_OFFSET;

// .NET --- Coded Tokens

typedef enum<BYTE> { TypeDef_64, TypeRef_64, TypeSpec_64 } TypeDefOrRefTag;

typedef struct
{
    if ( TypeDefOrRefSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.TypeDef == 1 && MetadataStream.Header.NumOfRecords.TypeDefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (MetadataStream.Header.MaskValid.TypeRef == 1 && MetadataStream.Header.NumOfRecords.TypeRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;
        if (MetadataStream.Header.MaskValid.TypeSpec == 1 && MetadataStream.Header.NumOfRecords.TypeSpecLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeSpecLength;

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

typedef enum<BYTE> { Field_65, Param_65, Property_65 } HasConstantTag;

typedef struct
{
    if ( HasConstantSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;

        if (MetadataStream.Header.MaskValid.Field == 1 && MetadataStream.Header.NumOfRecords.FieldLength > maximum) maximum = MetadataStream.Header.NumOfRecords.FieldLength;
        if (MetadataStream.Header.MaskValid.Param == 1 && MetadataStream.Header.NumOfRecords.ParamLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ParamLength;
        if (MetadataStream.Header.MaskValid.Property == 1 && MetadataStream.Header.NumOfRecords.PropertyLength > maximum) maximum = MetadataStream.Header.NumOfRecords.PropertyLength;

        HasConstantSize = (maximum < (1 << 14)) ? 2 : 4;
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
            HasConstantTag table : 2;
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
            HasConstantTag table : 2;
            DWORD index : 30;
        }
    }
    BitfieldEnablePadding();
} HasConstant;

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
        
        if (MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (MetadataStream.Header.MaskValid.Field == 1 && MetadataStream.Header.NumOfRecords.FieldLength > maximum) maximum = MetadataStream.Header.NumOfRecords.FieldLength;
        if (MetadataStream.Header.MaskValid.TypeRef == 1 && MetadataStream.Header.NumOfRecords.TypeRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;
        if (MetadataStream.Header.MaskValid.TypeDef == 1 && MetadataStream.Header.NumOfRecords.TypeDefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (MetadataStream.Header.MaskValid.Param == 1 && MetadataStream.Header.NumOfRecords.ParamLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ParamLength;

        if (MetadataStream.Header.MaskValid.InterfaceImpl == 1 && MetadataStream.Header.NumOfRecords.InterfaceImplLength > maximum) maximum = MetadataStream.Header.NumOfRecords.InterfaceImplLength;
        if (MetadataStream.Header.MaskValid.MemberRef == 1 && MetadataStream.Header.NumOfRecords.MemberRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MemberRefLength;
        if (MetadataStream.Header.MaskValid.Module == 1 && MetadataStream.Header.NumOfRecords.ModuleLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ModuleLength;
        if (MetadataStream.Header.MaskValid.DeclSecurity == 1 && MetadataStream.Header.NumOfRecords.DeclSecurityLength > maximum) maximum = MetadataStream.Header.NumOfRecords.DeclSecurityLength;
        if (MetadataStream.Header.MaskValid.Property == 1 && MetadataStream.Header.NumOfRecords.PropertyLength > maximum) maximum = MetadataStream.Header.NumOfRecords.PropertyLength;

        if (MetadataStream.Header.MaskValid.Event == 1 && MetadataStream.Header.NumOfRecords.EventLength > maximum) maximum = MetadataStream.Header.NumOfRecords.EventLength;
        if (MetadataStream.Header.MaskValid.StandAloneSig == 1 && MetadataStream.Header.NumOfRecords.StandAloneSigLength > maximum) maximum = MetadataStream.Header.NumOfRecords.StandAloneSigLength;
        if (MetadataStream.Header.MaskValid.ModuleRef == 1 && MetadataStream.Header.NumOfRecords.ModuleRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ModuleRefLength;
        if (MetadataStream.Header.MaskValid.TypeSpec == 1 && MetadataStream.Header.NumOfRecords.TypeSpecLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeSpecLength;
        if (MetadataStream.Header.MaskValid.Assembly == 1 && MetadataStream.Header.NumOfRecords.AssemblyLength > maximum) maximum = MetadataStream.Header.NumOfRecords.AssemblyLength;

        if (MetadataStream.Header.MaskValid.AssemblyRef == 1 && MetadataStream.Header.NumOfRecords.AssemblyRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.AssemblyRefLength;
        if (MetadataStream.Header.MaskValid.File == 1 && MetadataStream.Header.NumOfRecords.FileLength > maximum) maximum = MetadataStream.Header.NumOfRecords.FileLength;
        if (MetadataStream.Header.MaskValid.ExportedType == 1 && MetadataStream.Header.NumOfRecords.ExportedTypeLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ExportedTypeLength;
        if (MetadataStream.Header.MaskValid.ManifestResource == 1 && MetadataStream.Header.NumOfRecords.ManifestResourceLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ManifestResourceLength;

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

typedef enum<BYTE> { Field_67, Param_67 } HasFieldMarshalTag;

typedef struct
{
    if ( HasFieldMarshalSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.Field == 1 && MetadataStream.Header.NumOfRecords.FieldLength > maximum) maximum = MetadataStream.Header.NumOfRecords.FieldLength;
        if (MetadataStream.Header.MaskValid.Param == 1 && MetadataStream.Header.NumOfRecords.ParamLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ParamLength;

        HasFieldMarshalSize = (maximum < (1 << 15)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( HasFieldMarshalSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            HasFieldMarshalTag table : 1;
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
            HasFieldMarshalTag table : 1;
            DWORD index : 31;
        }
    }
    BitfieldEnablePadding();
} HasFieldMarshal;

typedef enum<BYTE> { TypeDef_68, Method_68, Assembly_68 } HasDeclSecurityTag;

typedef struct
{
    if ( HasDeclSecuritySize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.TypeDef == 1 && MetadataStream.Header.NumOfRecords.TypeDefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (MetadataStream.Header.MaskValid.Assembly == 1 && MetadataStream.Header.NumOfRecords.AssemblyLength > maximum) maximum = MetadataStream.Header.NumOfRecords.AssemblyLength;

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

typedef enum<BYTE> { TypeDef_69, TypeRef_69, ModuleRef_69, Method_69, TypeSpec_69 } MemberRefParentTag;

typedef struct
{
    if ( MemberRefParentSize == 0)
    {
        // calculate coded token size
        local int maximum = 0;
        if (MetadataStream.Header.MaskValid.TypeDef == 1 && MetadataStream.Header.NumOfRecords.TypeDefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (MetadataStream.Header.MaskValid.TypeRef == 1 && MetadataStream.Header.NumOfRecords.TypeRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;
        if (MetadataStream.Header.MaskValid.ModuleRef == 1 && MetadataStream.Header.NumOfRecords.ModuleRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ModuleRefLength;
        if (MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (MetadataStream.Header.MaskValid.TypeSpec == 1 && MetadataStream.Header.NumOfRecords.TypeSpecLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeSpecLength;

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

typedef enum<BYTE> { Event_70, Property_70 } HasSemanticsTag;

typedef struct
{
    if ( HasSemanticsSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.Event == 1 && MetadataStream.Header.NumOfRecords.EventLength > maximum) maximum = MetadataStream.Header.NumOfRecords.EventLength;
        if (MetadataStream.Header.MaskValid.Property == 1 && MetadataStream.Header.NumOfRecords.PropertyLength > maximum) maximum = MetadataStream.Header.NumOfRecords.PropertyLength;

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

typedef enum<BYTE> { Method_71, MemberRef_71 } MethodDefOrRefTag;

typedef struct
{
    if ( MethodDefOrRefSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (MetadataStream.Header.MaskValid.MemberRef == 1 && MetadataStream.Header.NumOfRecords.MemberRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MemberRefLength;

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

typedef enum<BYTE> { Field_72, Method_72 } MemberForwardedTag;

typedef struct
{
    if ( MemberForwardedSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.Field == 1 && MetadataStream.Header.NumOfRecords.FieldLength > maximum) maximum = MetadataStream.Header.NumOfRecords.FieldLength;
        if (MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MethodLength;

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

typedef enum<BYTE> { File_73, AssemblyRef_73, ExportedType_73 } ImplementationTag;

typedef struct
{
    if ( ImplementationSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.File == 1 && MetadataStream.Header.NumOfRecords.FileLength > maximum) maximum = MetadataStream.Header.NumOfRecords.FileLength;
        if (MetadataStream.Header.MaskValid.AssemblyRef == 1 && MetadataStream.Header.NumOfRecords.AssemblyRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.AssemblyRefLength;
        if (MetadataStream.Header.MaskValid.ExportedType == 1 && MetadataStream.Header.NumOfRecords.ExportedTypeLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ExportedTypeLength;

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

typedef enum<BYTE> { TypeRef_74, TypeDef_74, Method_74, MemberRef_74, String_74 } CustomAttributeTypeTag;

typedef struct
{
    if ( CustomAttributeTypeSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.TypeRef == 1 && MetadataStream.Header.NumOfRecords.TypeRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;
        if (MetadataStream.Header.MaskValid.TypeDef == 1 && MetadataStream.Header.NumOfRecords.TypeDefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MethodLength;
        if (MetadataStream.Header.MaskValid.MemberRef == 1 && MetadataStream.Header.NumOfRecords.MemberRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MemberRefLength;
        // if (MetadataStream.Header.MaskValid.String == 1 && MetadataStream.Header.NumOfRecords.StringLength > maximum) maximum = MetadataStream.Header.NumOfRecords.StringLength; // TODO: there is no String md table

        CustomAttributeTypeSize = (maximum < (1 << 13)) ? 2 : 4;
    }
    BitfieldDisablePadding();
    if ( CustomAttributeTypeSize == 2 )
    {
        if ( ReadUShort() == 0 )
        {
            WORD token <comment="null">;
        }
        else
        {
            CustomAttributeTypeTag table : 3;
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
            CustomAttributeTypeTag table : 3;
            DWORD index : 29;
        }
    }
    BitfieldEnablePadding();
} CustomAttributeType;

typedef enum<BYTE> { Module_75, ModuleRef_75, AssemblyRef_75, TypeRef_75 } ResolutionScopeTag;

typedef struct
{
    if ( ResolutionScopeSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.Module == 1 && MetadataStream.Header.NumOfRecords.ModuleLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ModuleLength;
        if (MetadataStream.Header.MaskValid.ModuleRef == 1 && MetadataStream.Header.NumOfRecords.ModuleRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.ModuleRefLength;
        if (MetadataStream.Header.MaskValid.AssemblyRef == 1 && MetadataStream.Header.NumOfRecords.AssemblyRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.AssemblyRefLength;
        if (MetadataStream.Header.MaskValid.TypeRef == 1 && MetadataStream.Header.NumOfRecords.TypeRefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeRefLength;

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

typedef enum<BYTE> { TypeDef_76, Method_76 } TypeOrMethodDefTag;

typedef struct
{
    if ( TypeOrMethodDefSize == 0 )
    {
        // calculate coded token size
        local int maximum = 0;
        
        if (MetadataStream.Header.MaskValid.TypeDef == 1 && MetadataStream.Header.NumOfRecords.TypeDefLength > maximum) maximum = MetadataStream.Header.NumOfRecords.TypeDefLength;
        if (MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > maximum) maximum = MetadataStream.Header.NumOfRecords.MethodLength;

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

// .NET --- RID Types

typedef struct
{
    if ( MetadataStream.Header.MaskValid.TypeDef == 1 && MetadataStream.Header.NumOfRecords.TypeDefLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} TypeDefRid <read=rid>;

typedef struct
{
    if ( MetadataStream.Header.MaskValid.Field == 1 && MetadataStream.Header.NumOfRecords.FieldLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} FieldRid <read=rid>;

typedef struct
{
    if ( MetadataStream.Header.MaskValid.Method == 1 && MetadataStream.Header.NumOfRecords.MethodLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} MethodRid <read=rid>;

typedef struct
{    
    if ( MetadataStream.Header.MaskValid.Param == 1 && MetadataStream.Header.NumOfRecords.ParamLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} ParamRid <read=rid>;

typedef struct
{    
    if ( MetadataStream.Header.MaskValid.Event == 1 && MetadataStream.Header.NumOfRecords.EventLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} EventRid <read=rid>;

typedef struct
{    
    if ( MetadataStream.Header.MaskValid.Property == 1 && MetadataStream.Header.NumOfRecords.PropertyLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} PropertyRid <read=rid>;

typedef struct
{    
    if ( MetadataStream.Header.MaskValid.ModuleRef == 1 && MetadataStream.Header.NumOfRecords.ModuleRefLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} ModuleRefRid <read=rid>;

typedef struct
{    
    if ( MetadataStream.Header.MaskValid.AssemblyRef == 1 && MetadataStream.Header.NumOfRecords.AssemblyRefLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} AssemblyRefRid <read=rid>;

typedef struct
{    
    if ( MetadataStream.Header.MaskValid.GenericParam == 1 && MetadataStream.Header.NumOfRecords.GenericParamLength > 0x10000 )
    {
        DWORD rid;
    }
    else
    {
        WORD rid;
    }
} GenericParamRid <read=rid>;

// .NET --- Headers

typedef struct
{
    DWORD COMIMAGE_FLAGS_ILONLY:1                <comment="0x00001  ">;
    DWORD COMIMAGE_FLAGS_32BITREQUIRED:1         <comment="0x00002  ">;
    DWORD COMIMAGE_FLAGS_IL_LIBRARY:1            <comment="0x00004  ">;
    DWORD COMIMAGE_FLAGS_STRONGNAMESIGNED:1      <comment="0x00008  ">;
    DWORD COMIMAGE_FLAGS_NATIVE_ENTRYPOINT:1     <comment="0x00010  ">;
    DWORD :1                                     <comment="0x00020  ",hidden=true>;
    DWORD :1                                     <comment="0x00040  ",hidden=true>;
    DWORD :1                                     <comment="0x00080  ",hidden=true>;
    DWORD :1                                     <comment="0x00100  ",hidden=true>;
    DWORD :1                                     <comment="0x00200  ",hidden=true>;
    DWORD :1                                     <comment="0x00400  ",hidden=true>;
    DWORD :1                                     <comment="0x00800  ",hidden=true>;
    DWORD :1                                     <comment="0x01000  ",hidden=true>;
    DWORD :1                                     <comment="0x02000  ",hidden=true>;
    DWORD :1                                     <comment="0x04000  ",hidden=true>;
    DWORD :1                                     <comment="0x08000  ",hidden=true>;
    DWORD COMIMAGE_FLAGS_TRACKDEBUGDATA:1        <comment="0x10000  ">;
    DWORD COMIMAGE_FLAGS_32BITPREFERRED:1        <comment="0x20000  ">;
} COR20_HEADER_FLAGS;

typedef struct
{
    DWORD                 cb;              
    WORD                  MajorRuntimeVersion;
    WORD                  MinorRuntimeVersion;
    IMAGE_DATA_DIRECTORY  MetaData                <comment="To Metadata Header">;
    COR20_HEADER_FLAGS    Flags;
    DWORD                 EntryPointToken         <comment="MD token of the entry point">;
    IMAGE_DATA_DIRECTORY  Resources;
    IMAGE_DATA_DIRECTORY  StrongNameSignature;
    IMAGE_DATA_DIRECTORY  CodeManagerTable;
    IMAGE_DATA_DIRECTORY  VTableFixups;
    IMAGE_DATA_DIRECTORY  ExportAddressTableJumps;
    IMAGE_DATA_DIRECTORY  ManagedNativeHeader     <comment="Reserved, always 0">;
} IMAGE_COR20_HEADER;

typedef struct
{
    // storage signature
    DWORD Signature;
    WORD  MajorVersion;
    WORD  MinorVersion;
    DWORD ExtraData              <comment="Reserved, always 0">;
    DWORD VersionLength;
    BYTE  Version[VersionLength];

    // storage header
    WORD  Flags                  <comment="Reserved, always 0">;
    WORD  Streams                <comment="Number of streams">;
} GENERAL_METADATA_HEADER;

typedef struct
{
    DWORD Offset <comment=CommentStreamHeaderOffset>;
    DWORD Size;

    local int nameLen = ((ReadStringLength(FTell()) + 3) >> 2) << 2;
    BYTE  Name[nameLen];
} STREAM_HEADER <read=ReadStreamHeader>;

typedef struct (WORD streams)
{
    STREAM_HEADER StreamHeaderArr[streams]  <optimize=false>;
} STREAM_HEADER_ARR;

typedef struct
{
    BYTE StringSize:1 <comment="0x1: #String stream uses a 4-byte index">;
    BYTE GuidSize:1   <comment="0x2: #GUID stream uses a 4-byte index">;
    BYTE BlobSize:1   <comment="0x4: #Blob stream uses a 4-byte index">;
} HEAP_OFFSET_SIZES_MASK;

typedef struct
{
    QWORD Module:1                 <comment="RID Type: 00, Token Type: 0x00000000">;
    QWORD TypeRef:1                <comment="RID Type: 01, Token Type: 0x01000000">;
    QWORD TypeDef:1                <comment="RID Type: 02, Token Type: 0x02000000">;
    QWORD FieldPtr:1               <comment="RID Type: 03, Token Type: none">;
    QWORD Field:1                  <comment="RID Type: 04, Token Type: 0x04000000">;
    QWORD MethodPtr:1              <comment="RID Type: 05, Token Type: none">;
    QWORD Method:1                 <comment="RID Type: 06, Token Type: 0x06000000">;
    QWORD ParamPtr:1               <comment="RID Type: 07, Token Type: none">;
    QWORD Param:1                  <comment="RID Type: 08, Token Type: 0x08000000">;
    QWORD InterfaceImpl:1          <comment="RID Type: 09, Token Type: 0x09000000">;
    QWORD MemberRef:1              <comment="RID Type: 10, Token Type: 0x0A000000">;
    QWORD Constant:1               <comment="RID Type: 11, Token Type: none">;
    QWORD CustomAttribute:1        <comment="RID Type: 12, Token Type: 0x0C000000">;
    QWORD FieldMarshal:1           <comment="RID Type: 13, Token Type: none">;
    QWORD DeclSecurity:1           <comment="RID Type: 14, Token Type: 0x0E000000">;
    QWORD ClassLayout:1            <comment="RID Type: 15, Token Type: none">;
    QWORD FieldLayout:1            <comment="RID Type: 16, Token Type: none">;
    QWORD StandAloneSig:1          <comment="RID Type: 17, Token Type: 0x11000000">;
    QWORD EventMap:1               <comment="RID Type: 18, Token Type: none">;
    QWORD EventPtr:1               <comment="RID Type: 19, Token Type: none">;
    QWORD Event:1                  <comment="RID Type: 20, Token Type: 0x14000000">;
    QWORD PropertyMap:1            <comment="RID Type: 21, Token Type: none">;
    QWORD PropertyPtr:1            <comment="RID Type: 22, Token Type: none">;
    QWORD Property:1               <comment="RID Type: 23, Token Type: 0x17000000">;
    QWORD MethodSemantics:1        <comment="RID Type: 24, Token Type: none">;
    QWORD MethodImpl:1             <comment="RID Type: 25, Token Type: none">;
    QWORD ModuleRef:1              <comment="RID Type: 26, Token Type: 0x1A000000">;
    QWORD TypeSpec:1               <comment="RID Type: 27, Token Type: 0x1B000000">;
    QWORD ImplMap:1                <comment="RID Type: 28, Token Type: none">;
    QWORD FieldRVA:1               <comment="RID Type: 29, Token Type: none">;
    QWORD ENCLog:1                 <comment="RID Type: 30, Token Type: none">;
    QWORD ENCMap:1                 <comment="RID Type: 31, Token Type: none">;
    QWORD Assembly:1               <comment="RID Type: 32, Token Type: 0x20000000">;
    QWORD AssemblyProcessor:1      <comment="RID Type: 33, Token Type: none">;
    QWORD AssemblyOS:1             <comment="RID Type: 34, Token Type: none">;
    QWORD AssemblyRef:1            <comment="RID Type: 35, Token Type: 0x23000000">;
    QWORD AssemblyRefProcessor:1   <comment="RID Type: 36, Token Type: none">;
    QWORD AssemblyRefOS:1          <comment="RID Type: 37, Token Type: none">;
    QWORD File:1                   <comment="RID Type: 38, Token Type: 0x26000000">;
    QWORD ExportedType:1           <comment="RID Type: 39, Token Type: 0x27000000">;
    QWORD ManifestResource:1       <comment="RID Type: 40, Token Type: 0x28000000">;
    QWORD NestedClass:1            <comment="RID Type: 41, Token Type: none">;
    QWORD GenericParam:1           <comment="RID Type: 42, Token Type: none">;
    QWORD MethodSpec:1             <comment="RID Type: 43, Token Type: 0x2B000000">;
    QWORD GenericParamConstraint:1 <comment="RID Type: 44, Token Type: none">;
} METADATA_TABLE_RID;

typedef struct (METADATA_TABLE_RID& mask)
{
    if ( mask.Module == 1 )                 DWORD ModuleLength;
    if ( mask.TypeRef == 1 )                DWORD TypeRefLength;
    if ( mask.TypeDef == 1 )                DWORD TypeDefLength;
    if ( mask.FieldPtr == 1 )               DWORD FieldPtrLength;
    if ( mask.Field == 1 )                  DWORD FieldLength;
    if ( mask.MethodPtr == 1 )              DWORD MethodPtrLength;
    if ( mask.Method == 1 )                 DWORD MethodLength;
    if ( mask.ParamPtr == 1 )               DWORD ParamPtrLength;
    if ( mask.Param == 1 )                  DWORD ParamLength;
    if ( mask.InterfaceImpl == 1 )          DWORD InterfaceImplLength;
    if ( mask.MemberRef == 1 )              DWORD MemberRefLength;
    if ( mask.Constant == 1 )               DWORD ConstantLength;
    if ( mask.CustomAttribute == 1 )        DWORD CustomAttributeLength;
    if ( mask.FieldMarshal == 1 )           DWORD FieldMarshalLength;
    if ( mask.DeclSecurity == 1 )           DWORD DeclSecurityLength;
    if ( mask.ClassLayout == 1 )            DWORD ClassLayoutLength;
    if ( mask.FieldLayout == 1 )            DWORD FieldLayoutLength;
    if ( mask.StandAloneSig == 1 )          DWORD StandAloneSigLength;
    if ( mask.EventMap == 1 )               DWORD EventMapLength;
    if ( mask.EventPtr == 1 )               DWORD EventPtrLength;
    if ( mask.Event == 1 )                  DWORD EventLength;
    if ( mask.PropertyMap == 1 )            DWORD PropertyMapLength;
    if ( mask.PropertyPtr == 1 )            DWORD PropertyPtrLength;
    if ( mask.Property == 1 )               DWORD PropertyLength;
    if ( mask.MethodSemantics == 1 )        DWORD MethodSemanticsLength;
    if ( mask.MethodImpl == 1 )             DWORD MethodImplLength;
    if ( mask.ModuleRef == 1 )              DWORD ModuleRefLength;
    if ( mask.TypeSpec == 1 )               DWORD TypeSpecLength;
    if ( mask.ImplMap == 1 )                DWORD ImplMapLength;
    if ( mask.FieldRVA == 1 )               DWORD FieldRVALength;
    if ( mask.ENCLog == 1 )                 DWORD ENCLogLength;
    if ( mask.ENCMap == 1 )                 DWORD ENCMapLength;
    if ( mask.Assembly == 1 )               DWORD AssemblyLength;
    if ( mask.AssemblyProcessor == 1 )      DWORD AssemblyProcessorLength;
    if ( mask.AssemblyOS == 1 )             DWORD AssemblyOSLength;
    if ( mask.AssemblyRef == 1 )            DWORD AssemblyRefLength;
    if ( mask.AssemblyRefProcessor == 1 )   DWORD AssemblyRefProcessorLength;
    if ( mask.AssemblyRefOS == 1 )          DWORD AssemblyRefOSLength;
    if ( mask.File == 1 )                   DWORD FileLength;
    if ( mask.ExportedType == 1 )           DWORD ExportedTypeLength;
    if ( mask.ManifestResource == 1 )       DWORD ManifestResourceLength;
    if ( mask.NestedClass == 1 )            DWORD NestedClassLength;
    if ( mask.GenericParam == 1 )           DWORD GenericParamLength;
    if ( mask.MethodSpec == 1 )             DWORD MethodSpecLength;
    if ( mask.GenericParamConstraint == 1 ) DWORD GenericParamConstraintLength;
} METADATA_TABLE_RECORDS;

typedef struct
{
    DWORD                  Reserved <comment="Reserved, always 0">;
    BYTE                   MajorVersion <comment="Major version of the table schema">;
    BYTE                   MinorVersion <comment="Minor version of the table schema">;
    HEAP_OFFSET_SIZES_MASK HeapOffsetSizes <comment="Indicate width of stream indexes">;
    BYTE                   Rid <comment="Bit count of the maximal record index to all tables of the metadata">;
    METADATA_TABLE_RID     MaskValid <comment="Bit vector of present tables, each bit representing one table (1 if present).">;
    METADATA_TABLE_RID     Sorted <comment="Bit vector of sorted tables, each bit representing a respective table (1 if sorted).">;
    METADATA_TABLE_RECORDS NumOfRecords ( MaskValid );
} METADATA_STREAM_HEADER;

// .NET --- Metadata Tables

typedef struct
{
    WORD          Generation <comment="For edit-and-continue">;
    STRING_OFFSET Name;
    WORD          Mvid       <comment="Generated automatically">;
    WORD          EncId      <comment="For edit-and-continue">;
    WORD          EncBaseId  <comment="For edit-and-continue">;
} MODULE_TABLE <comment=CommentStringOffset(Name)>;

typedef struct
{
    ResolutionScope _ResolutionScope;
    STRING_OFFSET    Name;
    STRING_OFFSET    Namespace;
} TYPE_REF_RECORD <comment=GetFullName(Namespace, Name)>;

typedef struct ( DWORD typeRefLen )
{
    TYPE_REF_RECORD Records[typeRefLen] <optimize=false>;
} TYPE_REF_TABLE;

typedef struct
{
    DWORD Flags <comment=CommentTypeDefFlags(this)>;
    STRING_OFFSET Name;
    STRING_OFFSET Namespace;
    TypeDefOrRef Extends;
    FieldRid FieldList;
    MethodRid MethodList;
} TYPE_DEF_RECORD <comment=GetFullName(Namespace, Name)>;

string CommentTypeDefFlags(DWORD flag)
{
    local int visibility = flag & 7;
    local string output = "";
    switch ( visibility )
    {
        case 0: output = "private";            break;
        case 1: output = "public";             break;
        case 2: output = "nested public";      break;
        case 3: output = "nested private";     break;
        case 4: output = "nested family";      break;
        case 5: output = "nested assembly";    break;
        case 6: output = "nested famandassem"; break;
        case 7: output = "nested famorassem";  break;
    }
    local int layout = flag & 0x18;
    switch ( layout )
    {
        case 0x00: output += ", auto";       break;
        case 0x08: output += ", sequential"; break;
        case 0x10: output += ", explicit";   break;
    }
    local int typeSemantics = flag & 0x5A0;
    switch ( typeSemantics )
    {
        case 0x020: output += ", interface";   break;
        case 0x080: output += ", abstract";    break;
        case 0x100: output += ", sealed";      break;
        case 0x400: output += ", specialname"; break;
    }
    local int typeImplementation = (flag & 0x103000) >> 12;
    switch ( typeImplementation )
    {
        case 0x001: output += ", import";          break;
        case 0x002: output += ", serializable";    break;
        case 0x100: output += ", beforefieldinit"; break;
    }
    local int stringFormatting = (flag & 0x30000) >> 16;
    switch ( stringFormatting )
    {
        case 0: output += ", ansi";     break;
        case 1: output += ", unicode";  break;
        case 2: output += ", autochar"; break;
    }

    return output;
}

typedef struct ( DWORD typeDefLen )
{
    TYPE_DEF_RECORD Records[typeDefLen] <optimize=false>;
} TYPE_DEF_TABLE;

typedef struct
{
    FieldRid Field;
} FIELD_PTR_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD fieldPtrLen )
{
    FIELD_PTR_RECORD Records[fieldPtrLen] <optimize=false>;
} FIELD_PTR_TABLE;

typedef struct
{
    WORD Flags <comment=CommentFieldFlags(this)>;
    STRING_OFFSET Name;
    BLOB_OFFSET Signature;
} FIELD_RECORD <comment=CommentStringOffset(Name)>;

string CommentFieldFlags(WORD flag)
{
    local int accessibility = flag & 7;
    local string output = "";
    switch ( accessibility )
    {
        case 0: output = "privatescope"; break;
        case 1: output = "private";      break;
        case 2: output = "famandassem";  break;
        case 3: output = "assembly";     break;
        case 4: output = "family";       break;
        case 5: output = "famorassem";   break;
        case 6: output = "public";       break;
    }
    local int contract = flag & 0x2F0;
    switch ( contract )
    {
        case 0x010: output += ", static";         break;
        case 0x020: output += ", initonly";       break;
        case 0x040: output += ", literal";        break;
        case 0x080: output += ", notserialized";  break;
        case 0x200: output += ", specialname";    break;
    }
    // Interoperability
    if ( flag & 0x2000 ) output += ", pinvokeimpl";

    return output;
}

typedef struct ( DWORD fieldLen )
{
    FIELD_RECORD Records[fieldLen] <optimize=false>;
} FIELD_TABLE;

typedef struct
{
    MethodRid Method;
} METHOD_PTR_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD methodPtrLen )
{
    METHOD_PTR_RECORD Records[methodPtrLen] <optimize=false>;
} METHOD_PTR_TABLE;

typedef struct
{
    DWORD         RVA <comment=CommentRVA2FOA>;
    WORD          ImplFlags;
    WORD          Flags <comment=CommentMethodFlags(this)>;
    STRING_OFFSET Name;
    BLOB_OFFSET   Signature;
    ParamRid      ParamList;
} METHOD_RECORD <comment=CommentStringOffset(Name)>;

string CommentMethodFlags(WORD flag)
{
    local int accessibility = flag & 7;
    local string output = "";
    switch ( accessibility )
    {
        case 0: output = "privatescope"; break;
        case 1: output = "private";      break;
        case 2: output = "famandassem";  break;
        case 3: output = "assembly";     break;
        case 4: output = "family";       break;
        case 5: output = "famorassem";   break;
        case 6: output = "public";       break;
    }
    local int contract = flag & 0xF0;
    if ( contract & 0x010 ) output += ", static";
    if ( contract & 0x020 ) output += ", final";
    if ( contract & 0x040 ) output += ", virtual";
    if ( contract & 0x080 ) output += ", hidebysig";
    // v-table
    if ( flag & 0x100 ) output += ", newslot";
    local int implementation = flag & 0x2C08;
    switch ( implementation )
    {
        case 0x0400: output += ", abstract";     break;
        case 0x0800: output += ", specialname";  break;
        case 0x2000: output += ", pinvokeimpl";  break;
        case 0x0008: output += ", unmanagedexp"; break;
    }

    return output;
}

typedef struct ( DWORD methodLen )
{
    METHOD_RECORD Records[methodLen] <optimize=false>;
} METHOD_TABLE;

typedef struct
{
    ParamRid Param;
} PARAM_PTR_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD paramPtrLen )
{
    PARAM_PTR_RECORD Records[paramPtrLen] <optimize=false>;
} PARAM_PTR_TABLE;

typedef struct
{
    WORD Flags;
    WORD Sequence <comment="Sequence number of the parameter">;
    STRING_OFFSET Name;
} PARAM_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD paramLen )
{
    PARAM_RECORD Records[paramLen] <optimize=false>;
} PARAM_TABLE;

typedef struct
{
    TypeDefRid Class <comment="Class implementing the interface">;
    TypeDefOrRef Interface <comment="Implemented interface">;
} INTERFACE_IMPL_RECORD;

typedef struct ( DWORD interfaceImplLen )
{
    INTERFACE_IMPL_RECORD Records[interfaceImplLen] <optimize=false>;
} INTERFACE_IMPL_TABLE;

typedef struct
{
    MemberRefParent Class;
    STRING_OFFSET Name;
    BLOB_OFFSET Signature;
} MEMBER_REF_RECORD;

typedef struct ( DWORD memberRefLen )
{
    MEMBER_REF_RECORD Records[memberRefLen] <optimize=false>;
} MEMBER_REF_TABLE;

typedef struct
{
    WORD Type;
    HasConstant Parent;
    BLOB_OFFSET Value;
} CONSTANT_RECORD;

typedef struct ( DWORD constantLen )
{
    CONSTANT_RECORD Records[constantLen] <optimize=false>;
} CONSTANT_TABLE;

typedef struct
{
    HasCustomAttribute Parent;
    CustomAttributeType Type;
    BLOB_OFFSET Value;
} CUSTOM_ATTRIBUTE_RECORD;

typedef struct ( DWORD customAttributeLen )
{
    CUSTOM_ATTRIBUTE_RECORD Records[customAttributeLen] <optimize=false>;
} CUSTOM_ATTRIBUTE_TABLE;

typedef struct
{
    HasFieldMarshal Parent;
    BLOB_OFFSET NativeType;
} FIELD_MARSHAL_RECORD;

typedef struct ( DWORD fieldMarshalLength )
{
    FIELD_MARSHAL_RECORD Records[fieldMarshalLength] <optimize=false>;
} FIELD_MARSHAL_TABLE;

typedef struct
{
    WORD Action;
    HasDeclSecurity Parent;
    BLOB_OFFSET PermissionSet;
} DECL_SECURITY_RECORD;

typedef struct ( DWORD declSecurityLength )
{
    DECL_SECURITY_RECORD Records[declSecurityLength] <optimize=false>;
} DECL_SECURITY_TABLE;

typedef struct
{
    WORD PackingSize;
    DWORD ClassSize;
    TypeDefRid Parent;
} CLASS_LAYOUT_RECORD;

typedef struct ( DWORD classLayoutLength )
{
    CLASS_LAYOUT_RECORD Records[classLayoutLength] <optimize=false>;
} CLASS_LAYOUT_TABLE;

typedef struct
{
    DWORD OffSet;
    FieldRid Field;
} FIELD_LAYOUT_RECORD;

typedef struct ( DWORD fieldLayoutLength )
{
    FIELD_LAYOUT_RECORD Records[fieldLayoutLength] <optimize=false>;
} FIELD_LAYOUT_TABLE;

typedef struct
{
    BLOB_OFFSET Signature;
} STAND_ALONE_SIG_RECORD;

typedef struct ( DWORD standAloneSigLength )
{
    STAND_ALONE_SIG_RECORD Records[standAloneSigLength] <optimize=false>;
} STAND_ALONE_SIG_TABLE;

typedef struct
{
    TypeDefRid Parent;
    EventRid EventList;
} EVENT_MAP_RECORD;

typedef struct ( DWORD eventMapLength )
{
    EVENT_MAP_RECORD Records[eventMapLength] <optimize=false>;
} EVENT_MAP_TABLE;

typedef struct
{
    EventRid Event;
} EVENT_PTR_RECORD;

typedef struct ( DWORD eventPtrLength )
{
    EVENT_PTR_RECORD Records[eventPtrLength] <optimize=false>;
} EVENT_PTR_TABLE;

typedef struct
{
    WORD EventFlags;
    STRING_OFFSET Name;
    TypeDefOrRef EventType;
} EVENT_RECORD;

typedef struct ( DWORD eventLength )
{
    EVENT_RECORD Records[eventLength] <optimize=false>;
} EVENT_TABLE;

typedef struct
{
    TypeDefRid Parent;
    PropertyRid PropertyList;
} PROPERTY_MAP_RECORD;

typedef struct ( DWORD propertyMapLength )
{
    PROPERTY_MAP_RECORD Records[propertyMapLength] <optimize=false>;
} PROPERTY_MAP_TABLE;

typedef struct
{
    PropertyRid Property;
} PROPERTY_PTR_RECORD;

typedef struct ( DWORD propertyPtrLength )
{
    PROPERTY_PTR_RECORD Records[propertyPtrLength] <optimize=false>;
} PROPERTY_PTR_TABLE;

typedef struct
{
    WORD PropFlags;
    STRING_OFFSET Name;
    BLOB_OFFSET Type;
} PROPERTY_RECORD;

typedef struct ( DWORD propertyLength )
{
    PROPERTY_RECORD Records[propertyLength] <optimize=false>;
} PROPERTY_TABLE;

typedef struct
{
    WORD Semantic;
    MethodRid Method;
    HasSemantics Association;
} METHOD_SEMANTICS_RECORD;

typedef struct ( DWORD methodSemanticsLength )
{
    METHOD_SEMANTICS_RECORD Records[methodSemanticsLength] <optimize=false>;
} METHOD_SEMANTICS_TABLE;

typedef struct
{
    TypeDefRid Class;
    MethodDefOrRef MethodBody;
    MethodDefOrRef MethodDeclaration;
} METHOD_IMPL_RECORD;

typedef struct ( DWORD methodImplLength )
{
    METHOD_IMPL_RECORD Records[methodImplLength] <optimize=false>;
} METHOD_IMPL_TABLE;

typedef struct
{
    STRING_OFFSET Name;
} MODULE_REF_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD moduleRefLength )
{
    MODULE_REF_RECORD Records[moduleRefLength] <optimize=false>;
} MODULE_REF_TABLE;

typedef struct
{
    BLOB_OFFSET Signature;
} TYPE_SPEC_RECORD;

typedef struct ( DWORD typeSpecLength )
{
    TYPE_SPEC_RECORD Records[typeSpecLength] <optimize=false>;
} TYPE_SPEC_TABLE;

typedef struct
{
    DWORD Token;
    DWORD FuncCode;
} ENC_LOG_RECORD;

typedef struct ( DWORD encLogLength )
{
    ENC_LOG_RECORD Records[encLogLength] <optimize=false>;
} ENC_LOG_TABLE;

typedef struct
{
    WORD MappingFlags;
    MemberForwarded memberForwarded;
    STRING_OFFSET ImportName;
    ModuleRefRid ImportScope;
} IMPL_MAP_RECORD;

typedef struct ( DWORD implMapLength )
{
    IMPL_MAP_RECORD Records[implMapLength] <optimize=false>;
} IMPL_MAP_TABLE;

typedef struct
{
    DWORD RVA;
    FieldRid Field;
} FIELD_RVA_RECORD;

typedef struct ( DWORD fieldRVALength )
{
    FIELD_RVA_RECORD Records[fieldRVALength] <optimize=false>;
} FIELD_RVA_TABLE;

typedef struct
{
    DWORD Token;
} ENC_MAP_RECORD;

typedef struct ( DWORD ENCMapLength )
{
    ENC_MAP_RECORD Records[ENCMapLength] <optimize=false>;
} ENC_MAP_TABLE;

typedef struct
{
    DWORD HashAlgId;
    WORD MajorVersion;
    WORD MinorVersion;
    WORD BuildNumber;
    WORD RevisionNumber;
    DWORD Flags;
    BLOB_OFFSET PublicKey;
    STRING_OFFSET Name;
    STRING_OFFSET Locale;
} ASSEMBLY_RECORD;

typedef struct ( DWORD assemblyLength )
{
    ASSEMBLY_RECORD Records[assemblyLength] <optimize=false>;
} ASSEMBLY_TABLE;

typedef struct
{
    DWORD Processor;
} ASSEMBLY_PROCESSOR_RECORD;

typedef struct ( DWORD assemblyProcessorLength )
{
    ASSEMBLY_PROCESSOR_RECORD Records[assemblyProcessorLength] <optimize=false>;
} ASSEMBLY_PROCESSOR_TABLE;

typedef struct
{
    DWORD OSPlatformId;
    DWORD OSMajorVersion;
    DWORD OSMinorVersion;
} ASSEMBLY_OS_RECORD;

typedef struct ( DWORD assemblyOSLength )
{
    ASSEMBLY_OS_RECORD Records[assemblyOSLength] <optimize=false>;
} ASSEMBLY_OS_TABLE;

typedef struct
{
    WORD MajorVersion;
    WORD MinorVersion;
    WORD BuildNumber;
    WORD RevisionNumber;
    DWORD Flags;
    BLOB_OFFSET PublicKeyOrToken;
    STRING_OFFSET Name;
    STRING_OFFSET Locale;
    BLOB_OFFSET HashValue;
} ASSEMBLY_REF_RECORD;

typedef struct ( DWORD assemblyRefLength )
{
    ASSEMBLY_REF_RECORD Records[assemblyRefLength] <optimize=false>;
} ASSEMBLY_REF_TABLE;

typedef struct
{
    DWORD Processor;
    AssemblyRefRid AssemblyRef;
} ASSEMBLY_REF_PROCESSOR_RECORD;

typedef struct ( DWORD assemblyRefProcessorLength )
{
    ASSEMBLY_REF_PROCESSOR_RECORD Records[assemblyRefProcessorLength] <optimize=false>;
} ASSEMBLY_REF_PROCESSOR_TABLE;

typedef struct
{
    DWORD OSPlatformId;
    DWORD OSMajorVersion;
    DWORD OSMinorVersion;
    AssemblyRefRid AssemblyRef;
} ASSEMBLY_REF_OS_RECORD;

typedef struct ( DWORD assemblyRefOSLength )
{
    ASSEMBLY_REF_OS_RECORD Records[assemblyRefOSLength] <optimize=false>;
} ASSEMBLY_REF_OS_TABLE;

typedef struct
{
    DWORD Flags;
    STRING_OFFSET Name;
    BLOB_OFFSET HashValue;
} FILE_RECORD;

typedef struct ( DWORD fileLength )
{
    FILE_RECORD Records[fileLength] <optimize=false>;
} FILE_TABLE;

typedef struct
{
    DWORD Flags;
    DWORD TypeDefId;
    STRING_OFFSET TypeName;
    STRING_OFFSET TypeNamespace;
    Implementation implementation;
} EXPORTED_TYPE_RECORD;

typedef struct ( DWORD exportedTypeLength )
{
    EXPORTED_TYPE_RECORD Records[exportedTypeLength] <optimize=false>;
} EXPORTED_TYPE_TABLE;

typedef struct
{
    DWORD Offset;
    DWORD Flags;
    STRING_OFFSET Name;
    Implementation implementation;
} MANIFEST_RESOURCE_RECORD;

typedef struct ( DWORD manifestResourceLength )
{
    MANIFEST_RESOURCE_RECORD Records[manifestResourceLength] <optimize=false>;
} MANIFEST_RESOURCE_TABLE;

typedef struct
{
    TypeDefRid NestedClass;
    TypeDefRid EnclosingClass;
} NESTED_CLASS_RECORD;

typedef struct ( DWORD nestedClassLength )
{
    NESTED_CLASS_RECORD Records[nestedClassLength] <optimize=false>;
} NESTED_CLASS_TABLE;

typedef struct
{
    WORD Number;
    WORD Flags;
    TypeOrMethodDef Owner;
    STRING_OFFSET Name;
} GENERIC_PARAM_RECORD;

typedef struct ( DWORD genericParamLength )
{
    GENERIC_PARAM_RECORD Records[genericParamLength] <optimize=false>;
} GENERIC_PARAM_TABLE;

typedef struct
{
    MethodDefOrRef Method;
    BLOB_OFFSET Instantiation;
} METHOD_SPEC_RECORD;

typedef struct ( DWORD methodSpecLength )
{
    METHOD_SPEC_RECORD Records[methodSpecLength] <optimize=false>;
} METHOD_SPEC_TABLE;

typedef struct
{
    GenericParamRid Owner;
    TypeDefOrRef Constraint;
} GENERIC_PARAM_CONSTRAINT_RECORD;

typedef struct ( DWORD genericParamConstraintLength )
{
    GENERIC_PARAM_CONSTRAINT_RECORD Records[genericParamConstraintLength] <optimize=false>;
} GENERIC_PARAM_CONSTRAINT_TABLE;

typedef struct ( METADATA_TABLE_RID& mask, METADATA_TABLE_RECORDS& records )
{
    if ( mask.Module == 1 )                 MODULE_TABLE ModuleTable;
    if ( mask.TypeRef == 1 )                TYPE_REF_TABLE TypeRefTable(records.TypeRefLength);
    if ( mask.TypeDef == 1 )                TYPE_DEF_TABLE TypeDefTable(records.TypeDefLength);
    if ( mask.FieldPtr == 1 )               FIELD_PTR_TABLE FieldPtrTable(records.FieldPtrLength);
    if ( mask.Field == 1 )                  FIELD_TABLE FieldTable(records.FieldLength);
    if ( mask.MethodPtr == 1 )              METHOD_PTR_TABLE MethodPtrTable(records.MethodPtrLength);
    if ( mask.Method == 1 )                 METHOD_TABLE MethodTable(records.MethodLength);
    if ( mask.ParamPtr == 1 )               PARAM_PTR_TABLE ParamPtrTable(records.ParamPtrLength);
    if ( mask.Param == 1 )                  PARAM_TABLE ParamTable(records.ParamLength);
    if ( mask.InterfaceImpl == 1 )          INTERFACE_IMPL_TABLE InterfaceImplTable(records.InterfaceImplLength);
    if ( mask.MemberRef == 1 )              MEMBER_REF_TABLE MemberRefTable(records.MemberRefLength);
    if ( mask.Constant == 1 )               CONSTANT_TABLE ConstantTable(records.ConstantLength);
    if ( mask.CustomAttribute == 1 )        CUSTOM_ATTRIBUTE_TABLE CustomAttributeTable(records.CustomAttributeLength);
    if ( mask.FieldMarshal == 1 )           FIELD_MARSHAL_TABLE FieldMarshalTable(records.FieldMarshalLength);
    if ( mask.DeclSecurity == 1 )           DECL_SECURITY_TABLE DeclSecurityTable(records.DeclSecurityLength);
    if ( mask.ClassLayout == 1 )            CLASS_LAYOUT_TABLE ClassLayoutTable(records.ClassLayoutLength);
    if ( mask.FieldLayout == 1 )            FIELD_LAYOUT_TABLE FieldLayoutTable(records.FieldLayoutLength);
    if ( mask.StandAloneSig == 1 )          STAND_ALONE_SIG_TABLE StandAloneSigTable(records.StandAloneSigLength);
    if ( mask.EventMap == 1 )               EVENT_MAP_TABLE EventMapTable(records.EventMapLength);
    if ( mask.EventPtr == 1 )               EVENT_PTR_TABLE EventPtrTable(records.EventPtrLength);
    if ( mask.Event == 1 )                  EVENT_TABLE EventTable(records.EventLength);
    if ( mask.PropertyMap == 1 )            PROPERTY_MAP_TABLE PropertyMapTable(records.PropertyMapLength);
    if ( mask.PropertyPtr == 1 )            PROPERTY_PTR_TABLE PropertyPtrTable(records.PropertyPtrLength);
    if ( mask.Property == 1 )               PROPERTY_TABLE PropertyTable(records.PropertyLength);
    if ( mask.MethodSemantics == 1 )        METHOD_SEMANTICS_TABLE MethodSemanticsTable(records.MethodSemanticsLength);
    if ( mask.MethodImpl == 1 )             METHOD_IMPL_TABLE MethodImplTable(records.MethodImplLength);
    if ( mask.ModuleRef == 1 )              MODULE_REF_TABLE ModuleRefTable(records.ModuleRefLength);
    if ( mask.TypeSpec == 1 )               TYPE_SPEC_TABLE TypeSpecTable(records.TypeSpecLength);
    if ( mask.ImplMap == 1 )                IMPL_MAP_TABLE ImplMapTable(records.ImplMapLength);
    if ( mask.FieldRVA == 1 )               FIELD_RVA_TABLE FieldRVATable(records.FieldRVALength);
    if ( mask.ENCLog == 1 )                 ENC_LOG_TABLE ENCLogTable(records.ENCLogLength);
    if ( mask.ENCMap == 1 )                 ENC_MAP_TABLE ENCMapTable(records.ENCMapLength);
    if ( mask.Assembly == 1 )               ASSEMBLY_TABLE AssemblyTable(records.AssemblyLength);
    if ( mask.AssemblyProcessor == 1 )      ASSEMBLY_PROCESSOR_TABLE AssemblyProcessorTable(records.AssemblyProcessorLength);
    if ( mask.AssemblyOS == 1 )             ASSEMBLY_OS_TABLE AssemblyOSTable(records.AssemblyOSLength);
    if ( mask.AssemblyRef == 1 )            ASSEMBLY_REF_TABLE AssemblyRefTable(records.AssemblyRefLength);
    if ( mask.AssemblyRefProcessor == 1 )   ASSEMBLY_REF_PROCESSOR_TABLE AssemblyRefProcessorTable(records.AssemblyRefProcessorLength);
    if ( mask.AssemblyRefOS == 1 )          ASSEMBLY_REF_OS_TABLE AssemblyRefOSTable(records.AssemblyRefOSLength);
    if ( mask.File == 1 )                   FILE_TABLE FileTable(records.FileLength);
    if ( mask.ExportedType == 1 )           EXPORTED_TYPE_TABLE ExportedTypeTable(records.ExportedTypeLength);
    if ( mask.ManifestResource == 1 )       MANIFEST_RESOURCE_TABLE ManifestResourceTable(records.ManifestResourceLength);
    if ( mask.NestedClass == 1 )            NESTED_CLASS_TABLE NestedClassTable(records.NestedClassLength);
    if ( mask.GenericParam == 1 )           GENERIC_PARAM_TABLE GenericParamTable(records.GenericParamLength);
    if ( mask.MethodSpec == 1 )             METHOD_SPEC_TABLE MethodSpecTable(records.MethodSpecLength);
    if ( mask.GenericParamConstraint == 1 ) GENERIC_PARAM_CONSTRAINT_TABLE GenericParamConstraintTable(records.GenericParamConstraintLength);
} METADATA_TABLES;

// .NET --- streams

typedef struct
{
    METADATA_STREAM_HEADER Header <bgcolor=cLtPurple>;
    METADATA_TABLES        Tables(Header.MaskValid, Header.NumOfRecords) <bgcolor=cLtGray>;
} METADATA_STREAM;

typedef struct
{
    BYTE str[ReadStringLength(FTell())];
} GENERIC_STRING <read=(str)>;

typedef struct
{
    FSeek(FTell() + 1); // skip the first null byte

    local int nextLen;
    for (nextLen = ReadStringLength(FTell()); nextLen > 1; nextLen = ReadStringLength(FTell()))
    {
        GENERIC_STRING str;
    }
} STRING_HEAP;

typedef struct (int len)
{
    if (len == 1) UBYTE len;
    if (len == 2) WORD len;
    if (len == 4) DWORD len;
} ENCODED_LEN <comment=CommentEncodedLen>;

int DecodeLength(ENCODED_LEN& _EncodedLen)
{
    local int masked = (_EncodedLen.len >> 6) & 3;
    if (masked == 3) {
        local int ori = _EncodedLen.len & 0xFFFFFF1F;
        return (ori >> 24) | ((ori >> 8) & 0xFF00) | ((ori & 0xFF00) << 8) | ((ori & 0xFF) << 24);
    }
    if (masked == 2) {
        return (_EncodedLen.len >> 8) | ((_EncodedLen.len & 0x3F) << 8);
    }
    return _EncodedLen.len;
}

int GetCompressedLen()
{
    local UBYTE nextByte = ReadUByte();
    if (nextByte == 0) return 0;
    if ((nextByte >> 6) == 2) return 2;
    if ((nextByte >> 6) == 3) return 4;
    return 1;
}

typedef struct (int headerSize)
{
    ENCODED_LEN length(headerSize);
    local int decodedLen = DecodeLength(length);
    if (decodedLen > 1) wchar_t str[decodedLen >> 1] <fgcolor=cDkPurple>;
    if (decodedLen & 1) BYTE tail;
} USER_STRING <comment=CommentUserString>;

typedef struct
{
    FSeek(FTell() + 1); // skip the first null byte

    local int _headerSize;
    for (_headerSize = GetCompressedLen(); _headerSize != 0; _headerSize = GetCompressedLen())
    {
        USER_STRING str(_headerSize);
    }
} USER_STRING_HEAP;

typedef struct (int headerSize)
{
    ENCODED_LEN length(headerSize);
    local int decodedLen = DecodeLength(length);
    BYTE data[decodedLen] <fgcolor=cDkPurple>;
} BLOB_DATA;

typedef struct
{
    FSeek(FTell() + 1); // skip the first null byte

    local int _headerSize;
    for ( _headerSize = GetCompressedLen(); _headerSize != 0; _headerSize = GetCompressedLen())
    {
        BLOB_DATA data(_headerSize);
    }
} BLOB_HEAP;

typedef struct (int size)
{
    BYTE data[size];
} GENERIC_STREM;

// IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR
void ParseDotNet()
{
    if ( (NtHeader.OptionalHeader.DataDirArray.COMRuntimedescriptor.VirtualAddress == 0) || (NtHeader.OptionalHeader.DataDirArray.COMRuntimedescriptor.Size == 0) )
    {
        return;
    }

    local ULONG dotNetDirFOA = RVA2FOA(NtHeader.OptionalHeader.DataDirArray.COMRuntimedescriptor.VirtualAddress);
    FSeek(dotNetDirFOA);
    IMAGE_COR20_HEADER DotNetDir <bgcolor=cLtPurple>;

    if ( (DotNetDir.MetaData.VirtualAddress == 0) || (DotNetDir.MetaData.Size == 0) )
    {
        Printf("Invalid Metadata header address 0x%X or size 0x%X\n", DotNetDir.MetaData.VirtualAddress, DotNetDir.MetaData.Size);
        return;
    }

    local ULONG metadataFOA = RVA2FOA(DotNetDir.MetaData.VirtualAddress);
    FSeek(metadataFOA);
    GENERAL_METADATA_HEADER Metadata <bgcolor=cLtPurple>;

    if ( Metadata.Signature != 0x424A5342 )
    {
        Printf("Invalid Metadata header signature: 0x%X\n", Metadata.Signature);
        return;
    }

    STREAM_HEADER_ARR StreamHeaders(Metadata.Streams) <bgcolor=cLtGray>;

    local int i = 0;
    local string streamName;
    for (i = 0; i < Metadata.Streams; i++)
    {
        streamName = StreamHeaders.StreamHeaderArr[i].Name;
        FSeek(metadataFOA + StreamHeaders.StreamHeaderArr[i].Offset);

        // Metadata tables
        if ( streamName == "#~" ) METADATA_STREAM MetadataStream <read="#~">;

        // Other streams
        if ( streamName == "#Strings" )
        {
            StringHeapLoc = FTell();
            StringHeapSize = StreamHeaders.StreamHeaderArr[i].Size;
            STRING_HEAP StringHeap <fgcolor=cDkPurple,read="#Strings">;
        }
        if ( streamName == "#GUID" )
        {
            GUIDLoc = FTell();
            GUIDSize = StreamHeaders.StreamHeaderArr[i].Size;
            GENERIC_STREM GuidStream(StreamHeaders.StreamHeaderArr[i].Size) <bgcolor=cLtPurple,read="#GUID">;
        }
        if ( streamName == "#Blob" )
        {
            BlobLoc = FTell();
            BlobSize = StreamHeaders.StreamHeaderArr[i].Size;
            BLOB_HEAP BlobStream <read="#Blob">;
        }
        if ( streamName == "#US" )
        {
            USLoc = FTell();
            USSize = StreamHeaders.StreamHeaderArr[i].Size;
            USER_STRING_HEAP UserStringHeap <read="#US">;
        }
    }
}

string ReadStreamHeader(STREAM_HEADER& StreamHeader)
{
    return StreamHeader.Name;
}

string CommentStreamHeaderOffset(DWORD offset)
{
    return CommentRVA2FOA(DotNetDir.MetaData.VirtualAddress + offset);
}

int GetStringRAW(int offset)
{
    if ( offset >= StringHeapSize || offset == 0 ) return 0;
    return StringHeapLoc + offset;
}

string CommentStringOffset(STRING_OFFSET& _StringOffset)
{
    local int raw = GetStringRAW(_StringOffset.offset);
    return raw ? ReadString(raw) : "";
}

int GetBlobRAW(int offset)
{
    if ( offset >= BlobSize || offset == 0) return 0;
    return BlobLoc + offset;
}

string CommentEncodedLen(ENCODED_LEN& _EncodedLen)
{
    return Str("0x%X", DecodeLength(_EncodedLen));
}

wstring CommentUserString(USER_STRING& _UserString)
{
    if (DecodeLength(_UserString.length) > 1) return _UserString.str;
    return L"";
}

string GetFullName(STRING_OFFSET& namespace, STRING_OFFSET& name)
{
    if ( namespace.offset == 0 ) return CommentStringOffset(name);
    return Str("%s.%s", CommentStringOffset(namespace), CommentStringOffset(name));
}

ParseDotNet();
