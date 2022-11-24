typedef struct
{
    TypeDefRid Parent;
    EventRid EventList;
} EVENT_MAP_RECORD;

typedef struct ( DWORD eventMapLength )
{
    EVENT_MAP_RECORD Records[eventMapLength] <optimize=false>;
} EVENT_MAP_TABLE;
