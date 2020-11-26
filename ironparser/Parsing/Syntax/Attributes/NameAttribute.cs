using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IronParser.Parsing.Syntax.Attributes
{
    class NameAttribute : Attribute
    {
        public string Name { get; set; }

        public NameAttribute(string name)
        {
            Name = name;
        }
    }
}
