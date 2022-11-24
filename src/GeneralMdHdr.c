// Inside MS .NET IL Assembler - Part 2 Chapter 4
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
