using IronParser.Parsing.Syntax;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class HConstructorParamsDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;
        private bool m_IsFirst;
        private bool m_IsDefault;

        public HConstructorParamsDeclarationVisitor(StringBuilder builder, bool isDefault)
        {
            m_Builder = builder;
            m_IsFirst = true;
            m_IsDefault = isDefault;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
            VisitValueDeclaration(boolDeclaration);
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            VisitValueDeclaration(floatDeclaration);
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            VisitIntDeclaration(intDeclaration);
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            VisitReferenceDeclaration(vector2fDeclaration);
        }

        private void VisitValueDeclaration(Declaration declaration)
        {
            if (m_IsDefault && !declaration.HasDefaultValue())
            {
                return;
            }

            if (!m_IsFirst)
            {
                m_Builder.Append(", ");
            }
            m_IsFirst = false;

            m_Builder.Append(declaration.CppType).Append(" ").Append(declaration.Name.ToLower());
        }

        private void VisitReferenceDeclaration(Declaration declaration)
        {
            if (m_IsDefault && !declaration.HasDefaultValue())
            {
                return;
            }

            if (!m_IsFirst)
            {
                m_Builder.Append(", ");
            }
            m_IsFirst = false;

            m_Builder.Append("const ").Append(declaration.CppType).Append("& ").Append(declaration.Name.ToLower());
        }
    }
}
