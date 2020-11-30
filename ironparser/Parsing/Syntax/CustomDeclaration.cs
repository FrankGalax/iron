using IronParser.CodeGen.Visitors;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.Parsing.Syntax
{
    class CustomDeclaration : Declaration
    {
        public CustomDeclaration(string name, string cppType, TypeInfo typeInfo) :
            base(name, cppType, typeInfo)
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
