typedef struct
{
    PropertyRid Property;
} PROPERTY_PTR_RECORD;

typedef struct ( DWORD propertyPtrLength )
{
    PROPERTY_PTR_RECORD Records[propertyPtrLength] <optimize=false>;
} PROPERTY_PTR_TABLE;
