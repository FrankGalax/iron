using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class FloatDeclaration : Declaration
    {
        public float Value { get; private set; }

        public FloatDeclaration(string name, float value, bool isPointer) :
            base(name, "float", isPointer)
        {
            Value = value;
        }

        public FloatDeclaration(string name, bool isPointer) :
            this(name, 0.0f, isPointer)
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
