using IronParser.Parsing.Syntax;

namespace IronParser.CodeGen.Visitors
{
    abstract class DeclarationVisitor
    {
        public abstract void VisitBoolDeclaration(BoolDeclaration boolDeclaration);
        public abstract void VisitIntDeclaration(IntDeclaration intDeclaration);
        public abstract void VisitFloatDeclaration(FloatDeclaration floatDeclaration);
    }
}
