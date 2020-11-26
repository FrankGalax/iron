using IronParser.Parsing.Syntax.Attributes.DeclarationAttributes;
using System.Reflection;
using System.Linq;
using System;

namespace IronParser.Parsing.Syntax.Attributes
{
    static class AttributeHelper
    {
        public static DeclarationAttribute GetDeclarationAttribute(string name)
        {
            var types = Assembly.GetAssembly(typeof(AttributeHelper)).GetTypes()
                .Where(p => p.IsClass && p.IsSubclassOf(typeof(DeclarationAttribute)));
            foreach (var type in types)
            { 
                var attrs = type.GetCustomAttributes();
                foreach (var attr in attrs)
                {
                    NameAttribute nameAttribute = attr as NameAttribute;
                    if (nameAttribute == null)
                        continue;

                    if (nameAttribute.Name == name)
                    {
                        return Activator.CreateInstance(type) as DeclarationAttribute;
                    }
                }
            }
            return null;
        }
    }
}
