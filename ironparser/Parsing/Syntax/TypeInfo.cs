using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.Parsing.Syntax
{
    class TypeInfo
    {
        public bool IsPointer { get; set; }
        public bool IsArray { get; set; }
        public bool IsConst { get; set; }
    }
}
