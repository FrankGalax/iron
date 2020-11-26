using System.Collections.Generic;
using System.Text;
using IronParser.Parsing.Syntax;
using IronParser.CodeGen.Visitors;
using System.IO;
using System;

namespace IronParser.CodeGen
{
    class CppCodeGenerator : CodeGenerator
    {
        public CppCodeGenerator(Class c) :
            base(c)
        {

        }

        public override void Generate()
        {
            H();
            Cpp();
        }

        private void H()
        {
            StringBuilder hBuilder = new StringBuilder();
            hBuilder.Append("#pragma once\n\n")
                .Append("class ")
                .Append(m_Class.Name)
                .Append("\n{\n")
            // public
                .Append("public:\n")
            // Constructor
                .Tab()
                .Append(m_Class.Name)
                .Append("();\n")
            // Destructor
                .Append("    ~")
                .Append(m_Class.Name)
                .Append("();\n");

            // Getters and setters
            ApplyVisitor(new CppHGetterSetterDeclarationVisitor(hBuilder));

            // protected
            hBuilder.Append("protected:\n");
            ApplyVisitor(new CppHDeclareGenDeclarationVisitor(hBuilder));
            hBuilder.Append("};");

            File.WriteAllText(m_Class.Name.ToLower() + ".h", hBuilder.ToString());
        }

        private void Cpp()
        {
            StringBuilder cppBuilder = new StringBuilder();

            cppBuilder.Append("#include <")
                .Append(m_Class.Name.ToLower())
                .Append(".h>\n\n")
            // Constructor
                .CppClassPrefix(m_Class.Name)
                .Append(m_Class.Name);

            if (m_Class.Declarations.Count > 0)
            {
                cppBuilder.Append("() : \n");
                ApplyVisitor(new CppCppConstructorDeclarationVisitor(cppBuilder));
            }
            cppBuilder.Append("{\n}\n\n")
            // Destructors
                .CppClassPrefix(m_Class.Name)
                .Append("~")
                .Append(m_Class.Name)
                .Append("();\n{\n}");

            File.WriteAllText(m_Class.Name.ToLower() + ".cpp", cppBuilder.ToString());
        }

        private void ApplyVisitor(DeclarationVisitor visitor)
        {
            foreach (Declaration declaration in m_Class.Declarations)
            {
                declaration.AcceptVisitor(visitor);
            }
        }
    }
}
