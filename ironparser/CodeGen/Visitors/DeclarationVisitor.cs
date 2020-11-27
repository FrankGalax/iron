using IronParser.Parsing.Syntax;

namespace IronParser.CodeGen.Visitors
{
    abstract class DeclarationVisitor
    {
        public abstract void VisitBoolDeclaration(BoolDeclaration boolDeclaration);
        public abstract void VisitIntDeclaration(IntDeclaration intDeclaration);
        public abstract void VisitFloatDeclaration(FloatDeclaration floatDeclaration);
        public abstract void VisitVector2fDeclaration(Vector2fDeclaration vector2fDeclaration);
        public abstract void VisitCustomDeclaration(CustomDeclaration customDeclaration);
    }
}
