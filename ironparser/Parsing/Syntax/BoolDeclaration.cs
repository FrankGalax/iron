using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class BoolDeclaration : Declaration
    {
        public bool Value { get; private set; }

        public BoolDeclaration(string Name, bool value) :
            base(Name, "bool")
        {
            Value = value;
        }

        public BoolDeclaration(string name) :
            this(name, false)
        {
        }

        public override bool HasDefaultValue()
        {
            return !Value;
        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitBoolDeclaration(this);
        }
    }
}
