using System;
using System.IO;
using IronParser.Lexing;
using IronParser.Parsing;
using IronParser.Parsing.Syntax;
using IronParser.CodeGen;
using System.Collections.Generic;
using System.Text;

namespace IronParser
{
    class Program
    {
        struct ClassPath
        {
            public string Name { get; set; }
            public string Path { get; set; }
        }

        static void Main(string[] args)
        {
            string[] filePaths = Directory.GetFiles("../../../../iron/src/", "*.iron", SearchOption.AllDirectories);
            List<ClassPath> classPaths = new List<ClassPath>();
            foreach (string filePath in filePaths)
            {
                string source = File.ReadAllText(filePath);

                Lexer lexer = new Lexer(source);
                Parser parser = new Parser(lexer);
                Class c = parser.Class();

                CodeGenerator codeGen = new CodeGenerator(c, filePath);
                codeGen.Generate();
                classPaths.Add(new ClassPath { Name = c.Name, Path = filePath });
            }

            StringBuilder builder = new StringBuilder();
            builder.Append("#include<data/componentbuilder.h>\n\n")
                .Append("#include <iron.h>\n");

            foreach (ClassPath classPath in classPaths)
            {
                if (classPath.Name.EndsWith("Component") && !classPath.Name.Equals("Component"))
                {
                    builder.Append("#include <").Append(classPath.Path.Substring(21).Replace("\\", "/").Replace(".iron", ".h")).Append(">\n");
                }
            }

            builder.Append("\n")
                .Append("ironBEGIN_NAMESPACE\n\n")
                .Append("Component* ComponentBuilder::BuildComponent(int classHash)\n")
                .Append("{\n")
                .Tab().Append("switch (classHash)\n")
                .Tab().Append("{\n");

            foreach (ClassPath classPath in classPaths)
            {
                if (classPath.Name.EndsWith("Component") && !classPath.Name.Equals("Component"))
                {
                    builder.Tab().Append("case ").Append(classPath.Name.GetStableHashCode()).Append(" : return new ").Append(classPath.Name).Append("();\n");
                }
            }

            builder.Tab().Append("}\n")
                .Tab().Append("return nullptr;\n")
                .Append("}\n\n")
                .Append("ironEND_NAMESPACE");

            File.WriteAllText("../../../../iron/src/data/componentbuilder.cpp", builder.ToString());
        }
    }
}
