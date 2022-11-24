typedef struct
{
    TypeDefRid Parent;
    PropertyRid PropertyList;
} PROPERTY_MAP_RECORD;

typedef struct ( DWORD propertyMapLength )
{
    PROPERTY_MAP_RECORD Records[propertyMapLength] <optimize=false>;
} PROPERTY_MAP_TABLE;
