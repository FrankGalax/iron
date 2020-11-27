using IronParser.CodeGen.Visitors;
using System.Collections.Generic;

namespace IronParser.Parsing.Syntax
{
    abstract class Declaration
    {
        public string Name { get; private set; }
        public string CppType { get; private set; }
        public List<FieldAttribute> Attributes { get; set; }
        public bool IsPointer { get; set; }
        public virtual bool NeedConstructor { get { return true; } }

        public Declaration(string name, string cppType, bool isPointer)
        {
            Name = name;
            CppType = cppType;
            IsPointer = isPointer;
        }

        public bool HasAttribute(string attribute)
        {
            foreach (FieldAttribute attr in Attributes)
            {
                if (attr.Name.Equals(attribute))
                {
                    return true;
                }
            }

            return false;
        }

        public abstract bool HasDefaultValue();

        public abstract void AcceptVisitor(DeclarationVisitor visitor);
    }
}
