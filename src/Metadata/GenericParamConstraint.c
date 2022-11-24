typedef struct
{
    GenericParamRid Owner;
    TypeDefOrRef Constraint;
} GENERIC_PARAM_CONSTRAINT_RECORD;

typedef struct ( DWORD genericParamConstraintLength )
{
    GENERIC_PARAM_CONSTRAINT_RECORD Records[genericParamConstraintLength] <optimize=false>;
} GENERIC_PARAM_CONSTRAINT_TABLE;
