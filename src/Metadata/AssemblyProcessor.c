typedef struct
{
    DWORD Processor;
} ASSEMBLY_PROCESSOR_RECORD;

typedef struct ( DWORD assemblyProcessorLength )
{
    ASSEMBLY_PROCESSOR_RECORD Records[assemblyProcessorLength] <optimize=false>;
} ASSEMBLY_PROCESSOR_TABLE;
