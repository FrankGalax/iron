using System;

namespace IronParser.Lexing
{
    class Token
    {
        public int Tag { get; private set; }

        public Token(int tag)
        {
            Tag = tag;
        }

        public override string ToString()
        {
            return "" + (Char)Tag;
        }
    }
}
