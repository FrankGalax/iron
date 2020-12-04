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

        public static int GetStableHashCode(this string str)
        {
            unchecked
            {
                int hash1 = 5381;
                int hash2 = hash1;

                for (int i = 0; i < str.Length && str[i] != '\0'; i += 2)
                {
                    hash1 = ((hash1 << 5) + hash1) ^ str[i];
                    if (i == str.Length - 1 || str[i + 1] == '\0')
                        break;
                    hash2 = ((hash2 << 5) + hash2) ^ str[i + 1];
                }

                return hash1 + (hash2 * 1566083941);
            }
        }
    }
}
