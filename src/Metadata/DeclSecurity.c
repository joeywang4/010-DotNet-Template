typedef struct
{
    WORD Action;
    HasDeclSecurity Parent;
    BLOB_OFFSET PermissionSet;
} DECL_SECURITY_RECORD;

typedef struct ( DWORD declSecurityLength )
{
    DECL_SECURITY_RECORD Records[declSecurityLength] <optimize=false>;
} DECL_SECURITY_TABLE;
