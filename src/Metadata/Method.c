typedef struct
{
    DWORD         RVA <comment=CommentRVA2FOA>;
    WORD          ImplFlags;
    WORD          Flags <comment=CommentMethodFlags(this)>;
    STRING_OFFSET Name;
    BLOB_OFFSET   Signature;
    ParamRid      ParamList;
} METHOD_RECORD <comment=CommentStringOffset(Name)>;

string CommentMethodFlags(WORD flag)
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
    local int contract = flag & 0xF0;
    if ( contract & 0x010 ) output += ", static";
    if ( contract & 0x020 ) output += ", final";
    if ( contract & 0x040 ) output += ", virtual";
    if ( contract & 0x080 ) output += ", hidebysig";
    // v-table
    if ( flag & 0x100 ) output += ", newslot";
    local int implementation = flag & 0x2C08;
    switch ( implementation )
    {
        case 0x0400: output += ", abstract";     break;
        case 0x0800: output += ", specialname";  break;
        case 0x2000: output += ", pinvokeimpl";  break;
        case 0x0008: output += ", unmanagedexp"; break;
    }

    return output;
}

typedef struct ( DWORD methodLen )
{
    METHOD_RECORD Records[methodLen] <optimize=false>;
} METHOD_TABLE;
