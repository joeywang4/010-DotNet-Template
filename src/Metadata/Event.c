typedef struct
{
    WORD EventFlags;
    STRING_OFFSET Name;
    TypeDefOrRef EventType;
} EVENT_RECORD;

typedef struct ( DWORD eventLength )
{
    EVENT_RECORD Records[eventLength] <optimize=false>;
} EVENT_TABLE;
