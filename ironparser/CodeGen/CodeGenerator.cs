using System.Collections.Generic;
using IronParser.Parsing.Syntax;

namespace IronParser.CodeGen
{
    class CodeGenerator
    {
        protected Class m_Class;

        public CodeGenerator(Class c)
        {
            m_Class = c;
        }

        public virtual void Generate()
        {

        }
    }
}
