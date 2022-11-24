typedef struct
{
    WORD Flags <comment=CommentFieldFlags(this)>;
    STRING_OFFSET Name;
    BLOB_OFFSET Signature;
} FIELD_RECORD <comment=CommentStringOffset(Name)>;

string CommentFieldFlags(WORD flag)
{
    local int accessibility = flag & 7;
    local string output = "";
    switch ( accessibility )
    {
        case 0: output = "privatescope"; break;
        case 1: output = "private";      break;
        case 2: output = "famandassem";  break;
        case 3: output = "assembly";     break;
        case 4: output = "family";       break;
        case 5: output = "famorassem";   break;
        case 6: output = "public";       break;
    }
    local int contract = flag & 0x2F0;
    switch ( contract )
    {
        case 0x010: output += ", static";         break;
        case 0x020: output += ", initonly";       break;
        case 0x040: output += ", literal";        break;
        case 0x080: output += ", notserialized";  break;
        case 0x200: output += ", specialname";    break;
    }
    // Interoperability
    if ( flag & 0x2000 ) output += ", pinvokeimpl";

    return output;
}

typedef struct ( DWORD fieldLen )
{
    FIELD_RECORD Records[fieldLen] <optimize=false>;
} FIELD_TABLE;
