typedef struct
{
    TypeDefRid Class <comment="Class implementing the interface">;
    TypeDefOrRef Interface <comment="Implemented interface">;
} INTERFACE_IMPL_RECORD;

typedef struct ( DWORD interfaceImplLen )
{
    INTERFACE_IMPL_RECORD Records[interfaceImplLen] <optimize=false>;
} INTERFACE_IMPL_TABLE;
