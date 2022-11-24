#include "src/Metadata/Tables.c"

typedef struct
{
    BYTE StringSize:1 <comment="0x1: #String stream uses a 4-byte index">;
    BYTE GuidSize:1   <comment="0x2: #GUID stream uses a 4-byte index">;
    BYTE BlobSize:1   <comment="0x4: #Blob stream uses a 4-byte index">;
} HEAP_OFFSET_SIZES_MASK;

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

typedef struct
{
    METADATA_STREAM_HEADER Header <bgcolor=cLtPurple>;
    // Defined in src/metadata/Tables.c
    METADATA_TABLES        Tables(Header.MaskValid, Header.NumOfRecords) <bgcolor=cLtGray>;
} METADATA_STREAM;
