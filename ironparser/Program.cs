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
            string[] filePaths = Directory.GetFiles("../../../../iron/src/", "*.iron", SearchOption.AllDirectories);
            foreach (string filePath in filePaths)
            {
                string source = File.ReadAllText(filePath);

                Lexer lexer = new Lexer(source);
                Parser parser = new Parser(lexer);
                Class c = parser.Class();

                CodeGenerator codeGen = new CodeGenerator(c, filePath);
                codeGen.Generate();
            }
        }
    }
}
