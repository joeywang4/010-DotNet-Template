typedef struct
{
    WORD Semantic;
    MethodRid Method;
    HasSemantics Association;
} METHOD_SEMANTICS_RECORD;

typedef struct ( DWORD methodSemanticsLength )
{
    METHOD_SEMANTICS_RECORD Records[methodSemanticsLength] <optimize=false>;
} METHOD_SEMANTICS_TABLE;
