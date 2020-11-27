using IronParser.CodeGen.Visitors;
using System.Collections.Generic;

namespace IronParser.Parsing.Syntax
{
    abstract class Declaration
    {
        public string Name { get; private set; }
        public string CppType { get; private set; }
        public List<DeclarationAttribute> Attributes { get; set; }

        public Declaration(string name, string cppType)
        {
            Name = name;
            CppType = cppType;
        }

        public bool HasAttribute(string attribute)
        {
            foreach (DeclarationAttribute declarationAttribute in Attributes)
            {
                if (declarationAttribute.Name.Equals(attribute))
                {
                    return true;
                }
            }

            return false;
        }

        public abstract void AcceptVisitor(DeclarationVisitor visitor);
    }
}
