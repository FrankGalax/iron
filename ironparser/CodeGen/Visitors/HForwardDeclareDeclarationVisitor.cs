using IronParser.Parsing.Syntax;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class HForwardDeclareDeclarationVisitor : DeclarationVisitor
    {
        public bool DeclaredAtLeastOne { get; private set; }

        private StringBuilder m_Builder;

        public HForwardDeclareDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
            DeclaredAtLeastOne = false;
        }

        public override void VisitBoolDeclaration(BoolDeclaration boolDeclaration)
        {
        }

        public override void VisitFloatDeclaration(FloatDeclaration floatDeclaration)
        {
        }

        public override void VisitIntDeclaration(IntDeclaration intDeclaration)
        {
        }

        public override void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration)
        {
        }

        public override void VisitStringDeclaration(StringDeclaration stringDeclaration)
        {
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            if (customDeclaration.IsPointer)
            {
                m_Builder.Append("class ").Append(customDeclaration.CppType).Append(";\n");
                DeclaredAtLeastOne = true;
            }
        }
    }
}
