
namespace IronParser.Lexing
{
    class Word : Token
    {
        public string Lexeme { get; set; }

        public Word(string lexeme, TagType tag) :
            base((int)tag)
        {
            Lexeme = lexeme;
        }

        public override string ToString()
        {
            return Lexeme;
        }
    }
}
