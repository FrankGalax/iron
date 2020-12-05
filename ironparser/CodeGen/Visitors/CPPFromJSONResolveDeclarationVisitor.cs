using IronParser.Parsing.Syntax;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class CPPFromJSONResolveDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;

        public CPPFromJSONResolveDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
            if (HandleDeclaration(boolDeclaration))
            {
                return;
            }
        }

        public override void VisitColorDeclaration(ColorDeclaration colorDeclaration)
        {
            if (HandleDeclaration(colorDeclaration))
            {
                return;
            }
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            if (HandleDeclaration(customDeclaration))
            {
                return;
            }

            if (customDeclaration.IsPointer)
            {

            }
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            if (HandleDeclaration(floatDeclaration))
            {
                return;
            }
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            if (HandleDeclaration(intDeclaration))
            {
                return;
            }
        }

        public override void VisitStringDeclaration(StringDeclaration stringDeclaration)
        {
            if (HandleDeclaration(stringDeclaration))
            {
                return;
            }
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            if (HandleDeclaration(vector2fDeclaration))
            {
                return;
            }
        }

        private bool HandleDeclaration(Declaration declaration)
        {
            if (declaration.HasAttribute("Transient"))
            {
                return true;
            }

            if (declaration.IsArray)
            {
                string lowerName = declaration.Name.ToLowerCamelCase();
                string variableName = lowerName.Substring(0, lowerName.Length - 1);
                m_Builder.Tab().Append("for (int i = 0; i < m_").Append(declaration.Name).Append(".size(); ++i)\n")
                    .Tab().Append("{\n")
                    .Tab().Tab().Append("JSON ").Append(variableName).Append("JSON(j[\"").Append(lowerName).Append("\"][i]);\n");

                m_Builder.Tab().Tab().Append("m_").Append(declaration.Name).Append("[i]")
                    .Append(declaration.IsPointer ? "->" : ".")
                    .Append("FromJSONResolve(&").Append(variableName).Append("JSON);\n");

                m_Builder.Tab().Append("}\n");

                return true;
            }

            if (declaration.HasAttribute("Enum"))
            {
                return true;
            }

            return false;
        }
    }
}
