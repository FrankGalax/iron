using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IronParser.Parsing.Syntax;
using System.Globalization;

namespace IronParser.CodeGen.Visitors
{
    class ConstructorDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;
        private bool m_IsFirst;

        public ConstructorDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
            m_IsFirst = true;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
            Prefix(boolDeclaration);
            m_Builder.Append(boolDeclaration.Value.ToString().ToLower());
            Suffix();
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            Prefix(floatDeclaration);
            string value = floatDeclaration.Value.ToString();
            value = value.Replace(',', '.');
            if (!value.Contains('.'))
            {
                value += '.';
            }
            value += 'f';
            m_Builder.Append(value);
            Suffix();
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            Prefix(intDeclaration);
            m_Builder.Append(intDeclaration.Value);
            Suffix();
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            throw new NotImplementedException();
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            throw new NotImplementedException();
        }

        private void Prefix(Declaration declaration)
        {
            if (m_IsFirst)
            {
                m_Builder.Append("    m_");
                m_IsFirst = false;
            }
            else
            {
                m_Builder.Append(",   m_");
            }
            m_Builder.Append(declaration.Name);
            m_Builder.Append("(");
        }

        private void Suffix()
        {
            m_Builder.Append(")\n");
        }
    }
}
