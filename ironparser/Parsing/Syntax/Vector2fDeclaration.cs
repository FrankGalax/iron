using IronParser.CodeGen.Visitors;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.Parsing.Syntax
{
    class Vector2fDeclaration : Declaration
    {
        public float XValue { get; private set; }
        public float YValue { get; private set; }

        public Vector2fDeclaration(string name, float xValue, float yValue, bool isPointer, bool isArray) :
            base(name, "Vector2f", isPointer, isArray)
        {
            XValue = xValue;
            YValue = yValue;
        }

        public Vector2fDeclaration(string name, bool isPointer, bool isArray) :
            this(name, 0.0f, 0.0f, isPointer, isArray)
        {

        }

        public override bool HasDefaultValue()
        {
            return XValue == 0.0f && YValue == 0.0f;
        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitVector2fDeclaration(this);
        }
    }
}
