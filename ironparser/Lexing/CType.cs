using System;

namespace IronParser.Lexing
{
    class CType : Word
    {
        public static readonly CType Int = new CType("int", TagType.Basic),
            Float = new CType("float", TagType.Basic),
            Bool = new CType("bool", TagType.Basic),
            Vector2f = new CType("Vector2f", TagType.Basic);

        public CType(String lexeme, TagType tag) :
            base(lexeme, tag)
        {
        }
    }
}
