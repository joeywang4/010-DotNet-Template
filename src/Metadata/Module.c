typedef struct
{
    WORD          Generation <comment="For edit-and-continue">;
    STRING_OFFSET Name;
    WORD          Mvid       <comment="Generated automatically">;
    WORD          EncId      <comment="For edit-and-continue">;
    WORD          EncBaseId  <comment="For edit-and-continue">;
} MODULE_TABLE <comment=CommentStringOffset(Name)>;
