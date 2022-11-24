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

wstring CommentUserString(USER_STRING& _UserString)
{
    if (DecodeLength(_UserString.length) > 1) return _UserString.str;
    return L"";
}
