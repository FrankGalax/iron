using System;

namespace IronParser.Parsing.Syntax.Attributes.DeclarationAttributes
{
    [Name("NoAccessors")]
    class NoAccessorDeclarationAttribute : DeclarationAttribute
    {
        public override void Apply(Declaration declaration)
        {
            declaration.HasAccessors = false;
        }
    }
}
