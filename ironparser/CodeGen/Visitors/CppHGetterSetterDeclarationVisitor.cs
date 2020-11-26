using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IronParser.Parsing.Syntax;

namespace IronParser.CodeGen.Visitors
{
    class CppHGetterSetterDeclarationVisitor : DeclarationVisitor
    {
        private StringBuilder m_Builder;

        public CppHGetterSetterDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
            VisitDeclaration(boolDeclaration);
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
            VisitDeclaration(floatDeclaration);
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
            VisitDeclaration(intDeclaration);
        }

        private void VisitDeclaration(Declaration declaration)
        {
            if (!declaration.HasAccessors)
                return;

            m_Builder.Tab()
                .Append("inline ")
                .Append(declaration.CppType)
                .Append(" Get")
                .Append(declaration.Name)
                .Append("() const { return m_")
                .Append(declaration.Name)
                .Append("; }\n")
                .Tab()
                .Append("inline void Set")
                .Append(declaration.Name)
                .Append("(")
                .Append(declaration.CppType)
                .Append(" value) { m_")
                .Append(declaration.Name)
                .Append(" = value; }\n");
        }
    }
}
