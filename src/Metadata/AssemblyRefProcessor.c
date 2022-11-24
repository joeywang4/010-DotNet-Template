typedef struct
{
    DWORD Processor;
    AssemblyRefRid AssemblyRef;
} ASSEMBLY_REF_PROCESSOR_RECORD;

typedef struct ( DWORD assemblyRefProcessorLength )
{
    ASSEMBLY_REF_PROCESSOR_RECORD Records[assemblyRefProcessorLength] <optimize=false>;
} ASSEMBLY_REF_PROCESSOR_TABLE;
