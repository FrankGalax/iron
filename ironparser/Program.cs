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
            string source = File.ReadAllText(args[0]);

            Lexer lexer = new Lexer(source);
            Parser parser = new Parser(lexer);
            Class c = parser.Class();
            c.Declarations.ForEach(p => p.ApplyAttributes());

            CppCodeGenerator codeGen = new CppCodeGenerator(c);
            codeGen.Generate();
        }
    }
}
