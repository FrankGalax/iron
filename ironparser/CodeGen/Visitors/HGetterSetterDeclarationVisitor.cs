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
            if (declaration.HasAttribute("NoAccessors"))
                return;

            m_Builder.Tab()
                .Append(declaration.CppType)
                .Append(" Get")
                .Append(declaration.Name)
                .Append("() const { return m_")
                .Append(declaration.Name)
                .Append("; }\n")
                .Tab()
                .Append("void Set")
                .Append(declaration.Name)
                .Append("(")
                .Append(declaration.CppType)
                .Append(" value) { m_")
                .Append(declaration.Name)
                .Append(" = value; }\n");
        }

        private void VisitReferenceDeclaration(Declaration declaration)
        {
            if (declaration.HasAttribute("NoAccessors"))
                return;
            
            if (declaration.HasAttribute("NonConstGetter"))
            {
                m_Builder.Tab()
                    .Append(declaration.CppType)
                    .Append("& Get")
                    .Append(declaration.Name)
                    .Append("() { return m_")
                    .Append(declaration.Name)
                    .Append("; }\n");
            }

            m_Builder.Tab()
                .Append("const ")
                .Append(declaration.CppType)
                .Append("& Get")
                .Append(declaration.Name)
                .Append("() const { return m_")
                .Append(declaration.Name)
                .Append("; }\n");

            if (!declaration.HasAttribute("ReadOnly"))
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
