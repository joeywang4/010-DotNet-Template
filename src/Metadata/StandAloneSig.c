typedef struct
{
    BLOB_OFFSET Signature;
} STAND_ALONE_SIG_RECORD;

typedef struct ( DWORD standAloneSigLength )
{
    STAND_ALONE_SIG_RECORD Records[standAloneSigLength] <optimize=false>;
} STAND_ALONE_SIG_TABLE;
