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
        public List<Declaration> Declarations { get; set; }
    }
}
