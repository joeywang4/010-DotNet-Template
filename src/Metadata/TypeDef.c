typedef struct
{
    DWORD Flags <comment=CommentTypeDefFlags(this)>;
    STRING_OFFSET Name;
    STRING_OFFSET Namespace;
    TypeDefOrRef Extends;
    FieldRid FieldList;
    MethodRid MethodList;
} TYPE_DEF_RECORD <comment=GetFullName(Namespace, Name)>;

typedef struct ( DWORD typeDefLen )
{
    TYPE_DEF_RECORD Records[typeDefLen] <optimize=false>;
} TYPE_DEF_TABLE;

string CommentTypeDefFlags(DWORD flag)
{
    local int visibility = flag & 7;
    local string output = "";
    switch ( visibility )
    {
        case 0: output = "private";            break;
        case 1: output = "public";             break;
        case 2: output = "nested public";      break;
        case 3: output = "nested private";     break;
        case 4: output = "nested family";      break;
        case 5: output = "nested assembly";    break;
        case 6: output = "nested famandassem"; break;
        case 7: output = "nested famorassem";  break;
    }
    local int layout = flag & 0x18;
    switch ( layout )
    {
        case 0x00: output += ", auto";       break;
        case 0x08: output += ", sequential"; break;
        case 0x10: output += ", explicit";   break;
    }
    local int typeSemantics = flag & 0x5A0;
    switch ( typeSemantics )
    {
        case 0x020: output += ", interface";   break;
        case 0x080: output += ", abstract";    break;
        case 0x100: output += ", sealed";      break;
        case 0x400: output += ", specialname"; break;
    }
    local int typeImplementation = (flag & 0x103000) >> 12;
    switch ( typeImplementation )
    {
        case 0x001: output += ", import";          break;
        case 0x002: output += ", serializable";    break;
        case 0x100: output += ", beforefieldinit"; break;
    }
    local int stringFormatting = (flag & 0x30000) >> 16;
    switch ( stringFormatting )
    {
        case 0: output += ", ansi";     break;
        case 1: output += ", unicode";  break;
        case 2: output += ", autochar"; break;
    }

    return output;
}
