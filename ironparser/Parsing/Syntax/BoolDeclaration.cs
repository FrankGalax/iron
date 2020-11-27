using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class BoolDeclaration : Declaration
    {
        public bool Value { get; private set; }

        public BoolDeclaration(string Name, bool value, bool isPointer) :
            base(Name, "bool", isPointer)
        {
            Value = value;
        }

        public BoolDeclaration(string name, bool isPointer) :
            this(name, false, isPointer)
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
