using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class IntDeclaration : Declaration
    {
        public int Value { get; private set; }

        public IntDeclaration(string name, int value, bool isPointer, bool isArray) :
            base(name, "int", isPointer, isArray)
        {
            Value = value;
        }

        public IntDeclaration(string name, bool isPointer, bool isArray) :
            this(name, 0, isPointer, isArray)
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
