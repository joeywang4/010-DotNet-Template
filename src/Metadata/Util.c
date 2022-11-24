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

string CommentStringOffset(STRING_OFFSET& _StringOffset)
{
    local int raw = GetStringRAW(_StringOffset.offset);
    return raw ? ReadString(raw) : "";
}

string GetFullName(STRING_OFFSET& namespace, STRING_OFFSET& name)
{
    if ( namespace.offset == 0 ) return CommentStringOffset(name);
    return Str("%s.%s", CommentStringOffset(namespace), CommentStringOffset(name));
}

int GetBlobRAW(int offset)
{
    if ( offset >= BlobSize || offset == 0) return 0;
    return BlobLoc + offset;
}

int GetStringRAW(int offset)
{
    if ( offset >= StringHeapSize || offset == 0 ) return 0;
    return StringHeapLoc + offset;
}
