using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IronParser.Parsing.Syntax
{
    class Class
    {
        public string Name { get; set; }
        public string ParentClassName { get; set; }
        public List<Declaration> Declarations { get; set; }
        public List<FieldAttribute> Attributes { get; set; }
        public List<string> Includes { get; set; }

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
    }
}
