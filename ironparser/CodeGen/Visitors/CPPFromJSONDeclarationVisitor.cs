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
                return true;
            }
            return false;
        }
    }
}
