using IronParser.CodeGen.Visitors;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.Parsing.Syntax
{
    class CustomDeclaration : Declaration
    {
        public override bool NeedConstructor { get { return false; } }

        public CustomDeclaration(string name, string cppType, bool isPointer) :
            base(name, cppType, isPointer)
        {

        }

        public override bool HasDefaultValue()
        {
            return true;
        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitCustomDeclaration(this);
        }
    }
}
