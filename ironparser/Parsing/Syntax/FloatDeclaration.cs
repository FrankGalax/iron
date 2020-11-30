using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class FloatDeclaration : Declaration
    {
        public float Value { get; private set; }

        public FloatDeclaration(string name, float value, TypeInfo typeInfo) :
            base(name, "float", typeInfo)
        {
            Value = value;
        }

        public FloatDeclaration(string name, TypeInfo typeInfo) :
            this(name, 0.0f, typeInfo)
        {

        }

        public override bool HasDefaultValue()
        {
            return Value == 0.0f;
        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitFloatDeclaration(this);
        }
    }
}
