int GetCompressedLen()
{
    local UBYTE nextByte = ReadUByte();
    if (nextByte == 0) return 0;
    if ((nextByte >> 6) == 2) return 2;
    if ((nextByte >> 6) == 3) return 4;
    return 1;
}

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

string CommentEncodedLen(ENCODED_LEN& _EncodedLen)
{
    return Str("0x%X", DecodeLength(_EncodedLen));
}
