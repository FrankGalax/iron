using IronParser.CodeGen.Visitors;
using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.Parsing.Syntax
{
    class StringDeclaration : Declaration
    { 
        public string Value { get; private set; }

        public StringDeclaration(string name, string value, bool isPointer, bool isArray) :
            base(name, "std::string", isPointer, isArray)
        {
            Value = value;
        }

        public StringDeclaration(string name, bool isPointer, bool isArray) :
            this(name, "", isPointer, isArray)
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
