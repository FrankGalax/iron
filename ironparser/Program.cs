using System;
using System.IO;
using IronParser.Lexing;
using IronParser.Parsing;
using IronParser.Parsing.Syntax;
using IronParser.CodeGen;

namespace IronParser
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] files = Directory.GetFiles("../../../../iron/src/", "*.iron", SearchOption.AllDirectories);
            foreach (string file in files)
            {
                string source = File.ReadAllText(file);

                Lexer lexer = new Lexer(source);
                Parser parser = new Parser(lexer);
                Class c = parser.Class();

                CppCodeGenerator codeGen = new CppCodeGenerator(c);
                codeGen.Generate();
            }
        }
    }
}
