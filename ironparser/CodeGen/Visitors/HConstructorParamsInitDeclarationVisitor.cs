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
        private bool m_IsDefault;

        public HConstructorParamsInitDeclarationVisitor(StringBuilder builder, bool isDefault)
        {
            m_Builder = builder;
            m_IsFirst = true;
            m_IsDefault = isDefault;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
            Prefix();

            if (m_IsDefault && !boolDeclaration.HasDefaultValue())
            {
                m_Builder.Append("m_").Append(boolDeclaration.Name).Append("(").Append(boolDeclaration.Value ? "true" : "false").Append(")");
            }
            else
            {
                VisitDeclaration(boolDeclaration);
            }
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            Prefix();

            if (m_IsDefault && !floatDeclaration.HasDefaultValue())
            {
                m_Builder.Append("m_")
                    .Append(floatDeclaration.Name)
                    .Append("(")
                    .Append(floatDeclaration.Value.ToString("0.0").Replace(",", "."))
                    .Append("f)");
            }
            else
            {
                VisitDeclaration(floatDeclaration);
            }
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            Prefix();

            if (m_IsDefault && !intDeclaration.HasDefaultValue())
            {
                m_Builder.Append("m_").Append(intDeclaration.Name).Append("(").Append(intDeclaration.Value).Append(")");
            }
            else
            {
                VisitDeclaration(intDeclaration);
            }
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            Prefix();

            if (m_IsDefault && !vector2fDeclaration.HasDefaultValue())
            {
                m_Builder.Append("m_")
                    .Append(vector2fDeclaration.Name)
                    .Append("(")
                    .Append(vector2fDeclaration.XValue.ToString("0.0").Replace(",", "."))
                    .Append("f, ")
                    .Append(vector2fDeclaration.YValue.ToString("0.0").Replace(",", ".")).Append("f)");
            }
            else
            {
                VisitDeclaration(vector2fDeclaration);
            }
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            Prefix();

            VisitDeclaration(customDeclaration);
        }

        private void Prefix()
        {
            if (!m_IsFirst)
            {
                m_Builder.Append(", ");
            }
            m_IsFirst = false;
        }

        private void VisitDeclaration(Declaration declaration)
        {
            m_Builder.Append("m_").Append(declaration.Name).Append("(").Append(declaration.Name.ToLower()).Append(")");
        }
    }
}
