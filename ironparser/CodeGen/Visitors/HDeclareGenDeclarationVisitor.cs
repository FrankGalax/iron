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
            VisitDeclaration(boolDeclaration, boolDeclaration.Value ? "true" : "false");
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            string valueString = floatDeclaration.Value == 0.0f ?
                "0.f" :
                floatDeclaration.Value.ToString("0.0f").Replace(",", ".");
            VisitDeclaration(floatDeclaration, valueString);
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            VisitDeclaration(intDeclaration, intDeclaration.Value.ToString());
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            VisitDeclaration(vector2fDeclaration, null);
        }

        public override void VisitStringDeclaration(StringDeclaration stringDeclaration)
        {
            VisitDeclaration(stringDeclaration, null);
        }

        public override void VisitColorDeclaration(ColorDeclaration colorDeclaration)
        {
            VisitDeclaration(colorDeclaration, null);
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            VisitDeclaration(customDeclaration, null);
        }

        private void VisitDeclaration(Declaration declaration, string valueString)
        {
            m_Builder.Tab();

            if (declaration.IsConst)
            {
                m_Builder.Append("const ");
            }

            if (declaration.IsArray)
            {
                m_Builder.Append("std::vector<");
            }

            m_Builder.Append(declaration.CppType)
                .Append(declaration.IsPointer ? "*" : "");

            if (declaration.IsArray)
            {
                m_Builder.Append(">");
            }

            m_Builder.Append(" m_")
                .Append(declaration.Name);
            
            if (!declaration.IsArray)
            {
                if (declaration.IsPointer)
                {
                    m_Builder.Append(" = nullptr");
                }
                else if (declaration.HasAttribute("Enum"))
                {
                    m_Builder.Append(" = ").Append(declaration.CppType).Append("::None");
                }
                else if (valueString != null)
                {
                    m_Builder.Append(" = ").Append(valueString);
                }
            }

            m_Builder.Append(";\n");
        }
    }
}
