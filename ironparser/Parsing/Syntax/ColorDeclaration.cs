using IronParser.CodeGen.Visitors;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.Parsing.Syntax
{
    class ColorDeclaration : Declaration
    {
        public float R { get; private set; }
        public float G { get; private set; }
        public float B { get; private set; }

        public ColorDeclaration(string name, float r, float g, float b, TypeInfo typeInfo) :
            base(name, "sf::Color", typeInfo)
        {
            R = r;
            G = g;
            B = b;
        }

        public ColorDeclaration(string name, TypeInfo typeInfo) :
            this(name, 0.0f, 0.0f, 0.0f, typeInfo)
        {
        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitColorDeclaration(this);
        }

        public override bool HasDefaultValue()
        {
            return R == 0.0f && G == 0.0f && B == 0.0f;
        }
    }
}
