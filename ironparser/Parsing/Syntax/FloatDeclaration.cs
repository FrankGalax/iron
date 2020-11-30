using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class FloatDeclaration : Declaration
    {
        public float Value { get; private set; }

        public FloatDeclaration(string name, float value, bool isPointer, bool isArray) :
            base(name, "float", isPointer, isArray)
        {
            Value = value;
        }

        public FloatDeclaration(string name, bool isPointer, bool isArray) :
            this(name, 0.0f, isPointer, isArray)
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
