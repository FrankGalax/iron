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
            //Cpp();
        }

        private void H()
        {
            StringBuilder hBuilder = new StringBuilder();
            hBuilder.Append("#pragma once\n\n")
                .Append("#include <iron.h>\n");

            foreach (string include in m_Class.Includes)
            {
                hBuilder.Append("#include <").Append(include).Append(">\n");
            }

            hBuilder.Append("\n")
                .Append("ironBEGIN_NAMESPACE\n\n")
                .Append("class ")
                .Append(m_Class.Name)
                .Append(" : public ")
                .Append(m_Class.ParentClassName)
                .Append("\n{\n")
            // public
                .Append("public:\n")
            // Constructor
                .Tab()
                .Append(m_Class.Name)
                .Append("(");

            ApplyVisitor(new HConstructorParamsDeclarationVisitor(hBuilder));

            hBuilder.Append(") : ");

            ApplyVisitor(new HConstructorParamsInitDeclarationVisitor(hBuilder));

            hBuilder.Append(" {}\n\n");

            // Getters and setters
            ApplyVisitor(new HGetterSetterDeclarationVisitor(hBuilder));

            // private
            hBuilder.Append("\nprivate:\n");
            ApplyVisitor(new HDeclareGenDeclarationVisitor(hBuilder));
            hBuilder.Append("};\n\n")
                .Append("ironEND_NAMESPACE");

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
                ApplyVisitor(new ConstructorDeclarationVisitor(cppBuilder));
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
