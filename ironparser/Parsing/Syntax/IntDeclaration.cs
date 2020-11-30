using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class IntDeclaration : Declaration
    {
        public int Value { get; private set; }

        public IntDeclaration(string name, int value, TypeInfo typeInfo) :
            base(name, "int", typeInfo)
        {
            Value = value;
        }

        public IntDeclaration(string name, TypeInfo typeInfo) :
            this(name, 0, typeInfo)
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
