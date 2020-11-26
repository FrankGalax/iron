
namespace IronParser.Lexing
{
    class Real : Token
    {
        public float Value { get; set; }

        public Real(float value) :
            base((int)TagType.Real)
        {
            Value = value;
        }

        public override string ToString()
        {
            return "" + Value;
        }
    }
}
