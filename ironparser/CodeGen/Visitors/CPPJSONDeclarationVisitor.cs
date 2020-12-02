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

            VisitDeclaration(boolDeclaration);
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

            VisitDeclaration(floatDeclaration);
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            if (HandleDeclaration(intDeclaration))
            {
                return;
            }

            VisitDeclaration(intDeclaration);
        }

        public override void VisitStringDeclaration(StringDeclaration stringDeclaration)
        {
            if (HandleDeclaration(stringDeclaration))
            {
                return;
            }

            VisitDeclaration(stringDeclaration);
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            if (HandleDeclaration(vector2fDeclaration))
            {
                return;
            }

            string variableName = vector2fDeclaration.Name.ToLowerCamelCase();
            m_Builder.Tab().Append("JSON ").Append(variableName).Append("Json;\n")
                .Tab().Append("nlohmann::json& ").Append(variableName).Append("J = ").Append(variableName).Append("Json.GetJ();\n")
                .Tab().Append(variableName).Append("J[\"x\"] = m_").Append(vector2fDeclaration.Name).Append(".GetX();\n")
                .Tab().Append(variableName).Append("J[\"y\"] = m_").Append(vector2fDeclaration.Name).Append(".GetY();\n")
                .Tab().Append("j[\"").Append(variableName).Append("\"] = ")
                .Append(variableName).Append("J;\n");
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

        private void VisitDeclaration(Declaration declaration)
        {
            m_Builder.Tab().Append("j[\"").Append(declaration.Name.ToLowerCamelCase()).Append("\"] = ")
                .Append("m_").Append(declaration.Name)
                .Append(";\n");
        }
    }
}
