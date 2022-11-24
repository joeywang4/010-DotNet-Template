// Inside MS .NET IL Assembler - Part 2 Chapter 4
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

string CommentStreamHeaderOffset(DWORD offset)
{
    return CommentRVA2FOA(DotNetDir.MetaData.VirtualAddress + offset);
}

string ReadStreamHeader(STREAM_HEADER& StreamHeader)
{
    return StreamHeader.Name;
}
