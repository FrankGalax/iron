
namespace IronParser.Lexing
{
    class Num : Token
    {
        public int Value { get; private set; }

        public Num(int value) :
            base((int)TagType.Num)
        {
            Value = value;
        }

        public override string ToString()
        {
            return "" + Value;
        }
    }
}
