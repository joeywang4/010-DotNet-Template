typedef struct
{
    WORD Flags;
    WORD Sequence <comment="Sequence number of the parameter">;
    STRING_OFFSET Name;
} PARAM_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD paramLen )
{
    PARAM_RECORD Records[paramLen] <optimize=false>;
} PARAM_TABLE;
