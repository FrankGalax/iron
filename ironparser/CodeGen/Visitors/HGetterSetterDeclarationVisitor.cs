using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IronParser.Parsing.Syntax;

namespace IronParser.CodeGen.Visitors
{
    class HGetterSetterDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;

        public HGetterSetterDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
            bool isBaseType = true;
            VisitValueDeclaration(boolDeclaration, isBaseType);
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            bool isBaseType = true;
            VisitValueDeclaration(floatDeclaration, isBaseType);
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            bool isBaseType = true;
            VisitValueDeclaration(intDeclaration, isBaseType);
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
            VisitReferenceDeclaration(vector2fDeclaration);
        }

        public override void VisitStringDeclaration(StringDeclaration stringDeclaration)
        {
            VisitReferenceDeclaration(stringDeclaration);
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            if (customDeclaration.IsPointer && !customDeclaration.IsArray)
            {
                bool isBaseType = false;
                VisitValueDeclaration(customDeclaration, isBaseType);
            }
            else
            {
                VisitReferenceDeclaration(customDeclaration);
            }
        }

        private void VisitValueDeclaration(Declaration declaration, bool isBaseType)
        {
            if (declaration.HasAttribute("NoAccessors"))
                return;

            if (!isBaseType && declaration.HasAttribute("NonConstGetter"))
            {
                m_Builder.Tab()
                    .Append(declaration.CppType)
                    .Append(declaration.IsPointer ? "* Get" : " Get")
                    .Append(declaration.Name)
                    .Append("() { return m_")
                    .Append(declaration.Name)
                    .Append("; }\n");
            }

            m_Builder.Tab()
                .Append(isBaseType ? "" : "const ")
                .Append(declaration.CppType)
                .Append(declaration.IsPointer ? "* Get" : " Get")
                .Append(declaration.Name)
                .Append("() const { return m_")
                .Append(declaration.Name)
                .Append("; }\n");

            if (!declaration.HasAttribute("ReadOnly") && !declaration.IsArray)
            {
                m_Builder.Tab()
                    .Append("void Set")
                    .Append(declaration.Name)
                    .Append("(")
                    .Append(declaration.CppType)
                    .Append(declaration.IsPointer ? "* " : " ")
                    .Append(declaration.Name.ToLower())
                    .Append(") { m_")
                    .Append(declaration.Name)
                    .Append(" = ")
                    .Append(declaration.Name.ToLower())
                    .Append("; }\n");
            }
        }

        private void VisitReferenceDeclaration(Declaration declaration)
        {
            if (declaration.HasAttribute("NoAccessors"))
                return;
            
            if (declaration.HasAttribute("NonConstGetter"))
            {
                m_Builder.Tab();

                if (declaration.IsArray)
                {
                    m_Builder.Append("std::vector<");
                }

                m_Builder.Append(declaration.CppType);

                if (declaration.IsPointer)
                {
                    m_Builder.Append("*");
                }

                if (declaration.IsArray)
                {
                    m_Builder.Append(">");
                }

                m_Builder.Append("& Get")
                    .Append(declaration.Name)
                    .Append("() { return m_")
                    .Append(declaration.Name)
                    .Append("; }\n");
            }

            m_Builder.Tab()
                .Append("const ");

            if (declaration.IsArray)
            {
                m_Builder.Append("std::vector<");
            }

            m_Builder.Append(declaration.CppType);

            if (declaration.IsPointer)
            {
                m_Builder.Append("*");
            }

            if (declaration.IsArray)
            {
                m_Builder.Append(">");
            }

            m_Builder.Append("& Get")
                .Append(declaration.Name)
                .Append("() const { return m_")
                .Append(declaration.Name)
                .Append("; }\n");

            if (!declaration.HasAttribute("ReadOnly") && !declaration.IsArray)
            {
                m_Builder.Tab()
                    .Append("void Set")
                    .Append(declaration.Name)
                    .Append("(const ")
                    .Append(declaration.CppType)
                    .Append("& value) { m_")
                    .Append(declaration.Name)
                    .Append(" = value; }\n");
            }
        }
    }
}
