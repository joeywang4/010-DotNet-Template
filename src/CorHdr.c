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

// Inside MS .NET IL Assembler - Part 2 Chapter 3
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
