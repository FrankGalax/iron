using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class BoolDeclaration : Declaration
    {
        public bool Value { get; private set; }

        public BoolDeclaration(string Name, bool value, TypeInfo typeInfo) :
            base(Name, "bool", typeInfo)
        {
            Value = value;
        }

        public BoolDeclaration(string name, TypeInfo typeInfo) :
            this(name, false, typeInfo)
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
