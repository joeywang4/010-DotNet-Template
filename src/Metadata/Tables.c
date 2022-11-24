#include "src/Metadata/Util.c"
#include "src/CodedTokens/Tokens.c"
#include "src/Rid/Rids.c"

// .NET --- Metadata Tables
#include "src/Metadata/Module.c"
#include "src/Metadata/TypeRef.c"
#include "src/Metadata/TypeDef.c"
#include "src/Metadata/FieldPtr.c"
#include "src/Metadata/Field.c"
#include "src/Metadata/MethodPtr.c"
#include "src/Metadata/Method.c"
#include "src/Metadata/ParamPtr.c"
#include "src/Metadata/Param.c"
#include "src/Metadata/InterfaceImpl.c"
#include "src/Metadata/MemberRef.c"
#include "src/Metadata/Constant.c"
#include "src/Metadata/CustomAttribute.c"
#include "src/Metadata/FieldMarshal.c"
#include "src/Metadata/DeclSecurity.c"
#include "src/Metadata/ClassLayout.c"
#include "src/Metadata/FieldLayout.c"
#include "src/Metadata/StandAloneSig.c"
#include "src/Metadata/EventMap.c"
#include "src/Metadata/EventPtr.c"
#include "src/Metadata/Event.c"
#include "src/Metadata/PropertyMap.c"
#include "src/Metadata/PropertyPtr.c"
#include "src/Metadata/Property.c"
#include "src/Metadata/MethodSemantics.c"
#include "src/Metadata/MethodImpl.c"
#include "src/Metadata/ModuleRef.c"
#include "src/Metadata/TypeSpec.c"
#include "src/Metadata/ImplMap.c"
#include "src/Metadata/FieldRVA.c"
#include "src/Metadata/ENCLog.c"
#include "src/Metadata/ENCMap.c"
#include "src/Metadata/Assembly.c"
#include "src/Metadata/AssemblyProcessor.c"
#include "src/Metadata/AssemblyOS.c"
#include "src/Metadata/AssemblyRef.c"
#include "src/Metadata/AssemblyRefProcessor.c"
#include "src/Metadata/AssemblyRefOS.c"
#include "src/Metadata/File.c"
#include "src/Metadata/ExportedType.c"
#include "src/Metadata/ManifestResource.c"
#include "src/Metadata/NestedClass.c"
#include "src/Metadata/GenericParam.c"
#include "src/Metadata/MethodSpec.c"
#include "src/Metadata/GenericParamConstraint.c"

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
