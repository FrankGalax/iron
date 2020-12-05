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
            if (declaration.HasAttribute("Transient"))
            {
                return true;
            }

            if (declaration.IsArray)
            {
                if (declaration.IsPointer)
                {
                    string lowerName = declaration.Name.ToLowerCamelCase();
                    string variableName = lowerName.Substring(0, lowerName.Length - 1);
                    m_Builder.Tab().Append("for (nlohmann::json& ").Append(variableName).Append("J : j[\"").Append(lowerName).Append("\"])\n")
                        .Tab().Append("{\n");

                    if (declaration.CppType.Equals("Entity"))
                    {
                        m_Builder.Tab().Tab().Append("Entity* ").Append(variableName).Append(" = new Entity();\n");
                    }
                    else if (declaration.CppType.EndsWith("Component"))
                    {
                        m_Builder.Tab().Tab().Append("Component* ").Append(variableName).Append(" = ComponentBuilder::BuildComponent(")
                            .Append(variableName).Append("J[\"class\"]);\n");
                    }

                    m_Builder.Tab().Tab().Append("JSON ").Append(variableName).Append("JSON(").Append(variableName).Append("J);\n")
                        .Tab().Tab().Append(variableName).Append("->FromJSON(&").Append(variableName).Append("JSON);\n")
                        .Tab().Tab().Append("m_").Append(declaration.Name).Append(".push_back(").Append(variableName).Append(");\n");
                    m_Builder.Tab().Append("}\n");
                }

                return true;
            }
            return false;
        }
    }
}
