using IronParser.Parsing.Syntax;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class HConstructorParamsInitDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;
        private bool m_IsFirst;

        public HConstructorParamsInitDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
            m_IsFirst = true;
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
            if (!m_IsFirst)
            {
                m_Builder.Append(", ");
            }
            m_IsFirst = false;
            m_Builder.Append("m_").Append(declaration.Name).Append("(").Append(declaration.Name.ToLower()).Append(")");
        }
    }
}
