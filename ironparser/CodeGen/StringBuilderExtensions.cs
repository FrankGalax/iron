using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IronParser.CodeGen
{
    static class StringBuilderExtensions
    {
        public static StringBuilder Tab(this StringBuilder builder)
        {
            builder.Append("    ");
            return builder;
        }

        public static StringBuilder CppClassPrefix(this StringBuilder builder, string className)
        {
            builder.Append(className).Append("::");
            return builder;
        }
    }
}
