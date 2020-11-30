using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class BoolDeclaration : Declaration
    {
        public bool Value { get; private set; }

        public BoolDeclaration(string Name, bool value, bool isPointer, bool isArray) :
            base(Name, "bool", isPointer, isArray)
        {
            Value = value;
        }

        public BoolDeclaration(string name, bool isPointer, bool isArray) :
            this(name, false, isPointer, isArray)
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
