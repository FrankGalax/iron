using IronParser.CodeGen.Visitors;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.Parsing.Syntax
{
    class StringDeclaration : Declaration
    { 
        public string Value { get; private set; }

        public StringDeclaration(string name, string value, TypeInfo typeInfo) :
            base(name, "std::string", typeInfo)
        {
            Value = value;
        }

        public StringDeclaration(string name, TypeInfo typeInfo) :
            this(name, "", typeInfo)
        {

        }

        public override bool HasDefaultValue()
        {
            return String.IsNullOrEmpty(Value);
        }

        public override void AcceptVisitor(DeclarationVisitor visitor)
        {
            visitor.VisitStringDeclaration(this);
        }
    }
}
