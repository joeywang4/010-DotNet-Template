typedef struct
{
    ParamRid Param;
} PARAM_PTR_RECORD <comment=CommentStringOffset(Name)>;

typedef struct ( DWORD paramPtrLen )
{
    PARAM_PTR_RECORD Records[paramPtrLen] <optimize=false>;
} PARAM_PTR_TABLE;
