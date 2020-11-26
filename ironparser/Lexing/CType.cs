using System;

namespace IronParser.Lexing
{
    class CType : Word
    {
        public static readonly CType Int = new CType("int", TagType.Basic, 4),
            Float = new CType("float", TagType.Basic, 8),
            Bool = new CType("bool", TagType.Basic, 1);

        public int Width { get; private set; }

        public CType(String lexeme, TagType tag, int width) :
            base(lexeme, tag)
        {
            Width = width;
        }

        public static bool Numeric(CType t)
        {
            return t == CType.Int || t == CType.Float;
        }

        public static CType Max(CType t1, CType t2)
        {
            if (!Numeric(t1) || !Numeric(t2))
                return null;
            if (t1 == CType.Float || t2 == CType.Float)
                return CType.Float;
            if (t1 == CType.Int || t2 == CType.Int)
                return CType.Int;
            return null;
        }
    }
}
