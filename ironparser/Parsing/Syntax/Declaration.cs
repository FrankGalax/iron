using IronParser.CodeGen.Visitors;
using IronParser.Parsing.Syntax.Attributes.DeclarationAttributes;
using System.Collections.Generic;

namespace IronParser.Parsing.Syntax
{
    abstract class Declaration
    {
        public string Name { get; private set; }
        public string CppType { get; private set; }
        public List<DeclarationAttribute> Attributes { get; set; }
        public bool HasAccessors { get; set; }

        public Declaration(string name, string cppType)
        {
            Name = name;
            CppType = cppType;
            HasAccessors = true;
        }

        public void ApplyAttributes()
        {
            foreach (DeclarationAttribute attribute in Attributes)
            {
                attribute.Apply(this);
            }
        }

        public abstract void AcceptVisitor(DeclarationVisitor visitor);
    }
}
