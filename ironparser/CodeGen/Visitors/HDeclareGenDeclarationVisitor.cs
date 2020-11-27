using System;
using IronParser.Parsing.Syntax;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class HDeclareGenDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;

        public HDeclareGenDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
            VisitDeclaration(boolDeclaration);
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            VisitDeclaration(floatDeclaration);
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            VisitDeclaration(intDeclaration);
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            VisitDeclaration(vector2fDeclaration);
        }

        private void VisitDeclaration(Declaration declaration)
        {
            m_Builder.Tab()
                .Append(declaration.CppType)
                .Append(" m_")
                .Append(declaration.Name)
                .Append(";\n");
        }
    }
}
