using IronParser.Parsing.Syntax;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class CPPFromJSONDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;

        public CPPFromJSONDeclarationVisitor(StringBuilder builder)
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

            string variableName = colorDeclaration.Name.ToLowerCamelCase();
            m_Builder.Tab().Append("m_").Append(colorDeclaration.Name).Append(" = sf::Color(j[\"").Append(variableName).Append("\"][\"r\"], j[\"")
                .Append(variableName).Append("\"][\"g\"], j[\"").Append(variableName).Append("\"][\"b\"], j[\"").Append(variableName)
                .Append("\"][\"a\"]);\n");
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            if (HandleDeclaration(customDeclaration))
            {
                return;
            }

            if (!customDeclaration.IsPointer)
            {
                string variableName = customDeclaration.Name.ToLowerCamelCase();
                m_Builder.Tab().Append("JSON ").Append(variableName).Append("JSON(j[\"").Append(variableName).Append("\"]);\n")
                    .Tab().Append("m_").Append(customDeclaration.Name).Append(".FromJSON(&").Append(variableName).Append("JSON);\n");
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
            m_Builder.Tab().Append("m_").Append(vector2fDeclaration.Name).Append(" = Vector2f(j[\"").Append(variableName).Append("\"][\"x\"], j[\"")
                .Append(variableName).Append("\"][\"y\"]);\n");
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
                m_Builder.Tab().Append("for (nlohmann::json& ").Append(variableName).Append("J : j[\"").Append(lowerName).Append("\"])\n")
                    .Tab().Append("{\n");

                if (declaration.IsPointer)
                {
                    if (declaration.CppType.Equals("Entity"))
                    {
                        m_Builder.Tab().Tab().Append("Entity* ").Append(variableName).Append(" = new Entity(")
                            .Append(variableName).Append("J[\"id\"], this);\n");
                    }
                    else if (declaration.CppType.EndsWith("Component"))
                    {
                        m_Builder.Tab().Tab().Append("Component* ").Append(variableName).Append(" = ComponentBuilder::BuildComponent(")
                            .Append(variableName).Append("J[\"class\"]);\n");
                        m_Builder.Tab().Tab().Append(variableName).Append("->SetOwner(this);\n");
                    }

                    m_Builder.Tab().Tab().Append("JSON ").Append(variableName).Append("JSON(").Append(variableName).Append("J);\n")
                        .Tab().Tab().Append(variableName).Append("->FromJSON(&").Append(variableName).Append("JSON);\n")
                        .Tab().Tab().Append("m_").Append(declaration.Name).Append(".push_back(").Append(variableName).Append(");\n");
                }
                else
                {
                    m_Builder.Tab().Tab().Append(declaration.CppType).Append(" ").Append(variableName).Append(";\n")
                        .Tab().Tab().Append("JSON ").Append(variableName).Append("JSON(").Append(variableName).Append("J);\n")
                        .Tab().Tab().Append(variableName).Append(".FromJSON(&").Append(variableName).Append("JSON);\n")
                        .Tab().Tab().Append("m_").Append(declaration.Name).Append(".push_back(").Append(variableName).Append(");\n");
                }

                m_Builder.Tab().Append("}\n");

                return true;
            }

            if (declaration.HasAttribute("Enum"))
            {
                string variableName = declaration.Name.ToLowerCamelCase();
                m_Builder.Tab().Append("m_").Append(declaration.Name).Append(" = static_cast<").Append(declaration.CppType)
                    .Append(">(").Append("j[\"").Append(variableName).Append("\"]);\n");
                return true;
            }

            return false;
        }

        private void VisitDeclaration(Declaration declaration)
        {
            string variableName = declaration.Name.ToLowerCamelCase();
            m_Builder.Tab().Append("m_").Append(declaration.Name).Append(" = j[\"").Append(variableName).Append("\"];\n");
        }
    }
}
