using IronParser.Parsing.Syntax;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class CPPJSONDeclarationVisitor : DeclarationVisitor
    {
        StringBuilder m_Builder;

        public CPPJSONDeclarationVisitor(StringBuilder builder)
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
            if (declaration.IsArray)
            {
                string lowerName = declaration.Name.ToLowerCamelCase();
                string variableName = lowerName.Substring(0, declaration.Name.Length - 1);
                m_Builder.Tab().Append("for (")
                    .Append(declaration.CppType)
                    .Append(declaration.IsPointer ? "* " : "& ")
                    .Append(variableName)
                    .Append(" : m_")
                    .Append(declaration.Name)
                    .Append(")\n")
                    .Tab().Append("{\n");

                m_Builder.Tab().Tab().Append("JSON subJSON;\n")
                    .Tab().Tab().Append(variableName)
                        .Append(declaration.IsPointer ? "->" : ".")
                        .Append("ToJSON(&subJSON);\n")
                    .Tab().Tab().Append("j[\"").Append(lowerName).Append("\"].push_back(subJSON.GetJ());\n");

                m_Builder.Tab().Append("}\n");
                return true;
            }
            return false;
        }
    }
}
