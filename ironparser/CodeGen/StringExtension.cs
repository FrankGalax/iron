using System;
using System.Collections.Generic;
using System.Text;

namespace IronParser.CodeGen
{
    static class StringExtension
    {
        public static String ToLowerCamelCase(this String str)
        {
            if (str.Length == 0)
            {
                return "";
            }
            if (str.Length == 1)
            {
                return str.ToLower();
            }
            return str.Substring(0, 1).ToLower() + str.Substring(1);
        }
    }
}
