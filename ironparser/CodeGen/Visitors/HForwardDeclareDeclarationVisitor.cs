using IronParser.Parsing.Syntax;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen.Visitors
{
    class HForwardDeclareDeclarationVisitor : DeclarationVisitor
    {
        public bool DeclaredAtLeastOne { get { return m_AddedDeclares.Count > 0; } }

        private StringBuilder m_Builder;
        private List<string> m_AddedDeclares;

        public HForwardDeclareDeclarationVisitor(StringBuilder builder)
        {
            m_Builder = builder;
            m_AddedDeclares = new List<string>();
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

        public override void VisitColorDeclaration(ColorDeclaration colorDeclaration)
        {
        }

        public override void VisitCustomDeclaration(CustomDeclaration customDeclaration)
        {
            if (customDeclaration.IsPointer && 
                !customDeclaration.HasAttribute("ForwardDeclareIgnore") && 
                !IsAlreadyAdded(customDeclaration.CppType))
            {
                m_Builder.Append("class ").Append(customDeclaration.CppType).Append(";\n");
                m_AddedDeclares.Add(customDeclaration.CppType);
            }
        }

        private bool IsAlreadyAdded(string declare)
        {
            foreach (string addedDeclare in m_AddedDeclares)
            {
                if (addedDeclare.Equals(declare))
                {
                    return true;
                }
            }

            return false;
        }
    }
}
