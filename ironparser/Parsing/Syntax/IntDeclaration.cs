using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class IntDeclaration : Declaration
    {
        public int Value { get; private set; }

        public IntDeclaration(string name, int value) :
            base(name, "int")
        {
            Value = value;
        }

        public IntDeclaration(string name) :
            this(name, 0)
        {

        }

        public override bool HasDefaultValue()
        {
            return Value == 0;
        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitIntDeclaration(this);
        }
    }
}
