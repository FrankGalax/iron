using IronParser.CodeGen.Visitors;

namespace IronParser.Parsing.Syntax
{
    class FloatDeclaration : Declaration
    {
        public float Value { get; private set; }

        public FloatDeclaration(string name, float value) :
            base(name, "float")
        {
            Value = value;
        }

        public FloatDeclaration(string name) :
            this(name, 0.0f)
        {

        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitFloatDeclaration(this);
        }
    }
}
