typedef struct
{
    EventRid Event;
} EVENT_PTR_RECORD;

typedef struct ( DWORD eventPtrLength )
{
    EVENT_PTR_RECORD Records[eventPtrLength] <optimize=false>;
} EVENT_PTR_TABLE;
