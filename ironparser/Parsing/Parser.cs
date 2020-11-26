using System.Collections.Generic;
using System;
using IronParser.Lexing;
using IronParser.Parsing.Syntax;
using IronParser.Parsing.Syntax.Attributes.DeclarationAttributes;
using IronParser.Parsing.Syntax.Attributes;

namespace IronParser.Parsing
{
    class Parser
    {
        private Lexer m_Lexer;
        private Token m_Look;

        public Parser(Lexer lexer)
        {
            m_Lexer = lexer;
            Move();
        }

        private void Move()
        {
            m_Look = m_Lexer.Scan();
        }

        private void Error(string message)
        {
            throw new Exception("near line " + Lexer.Line + ": " + message);
        }

        private void Match(int tag)
        {
            if (m_Look.Tag == tag)
                Move();
            else
                Error("syntax error");
        }

        private void Match(TagType tagType)
        {
            Match((int)tagType);
        }

        public Class Class()
        {
            Match(TagType.Class);
            Class c = new Class
            {
                Name = ((Word)m_Look).Lexeme
            };
            Match(TagType.Id);
            Match('{');
            c.Declarations = Declarations();
            Match('}');

            return c;
        }

        public List<Declaration> Declarations()
        {
            List<Declaration> declarations = new List<Declaration>();

            while (m_Look.Tag == (int)TagType.Basic || m_Look.Tag == '[')
            {
                Declaration decl = Declaration();
                Match(';');
                declarations.Add(decl);
            }
            return declarations;
        }

        private Declaration Declaration()
        {
            List<DeclarationAttribute> attrs = new List<DeclarationAttribute>();
            while (m_Look.Tag == '[')
            {
                DeclarationAttribute attr = DeclarationAttribute();
                attrs.Add(attr);
            }

            CType t = Type();
            Word word = (Word)m_Look;
            Match(TagType.Id);
            Declaration decl = null;

            if (m_Look.Tag == '=')
            {
                decl = InitializedDeclaration(t, word.Lexeme);
            }
            else
            {
                decl = UninitializedDeclaration(t, word.Lexeme);
            }

            if (decl == null)
            {
                Error("invalid declaration");
            }
            decl.Attributes = attrs;
            return decl;
        }

        private DeclarationAttribute DeclarationAttribute()
        {
            Match('[');
            Word word = (Word)m_Look;
            Match(TagType.Id);
            Match(']');

            return AttributeHelper.GetDeclarationAttribute(word.Lexeme);
        }

        private Declaration InitializedDeclaration(CType t, string name)
        {
            Match('=');
            if (t == CType.Bool)
            {
                return InitializedBool(name);
            }
            else if (t == CType.Int)
            {
                return InitializedInt(name);
            }
            else if (t == CType.Float)
            {
                return InitializedFloat(name);
            }
            return null;
        }

        private BoolDeclaration InitializedBool(string name)
        {
            if (m_Look.Tag == (int)TagType.True)
            {
                Match(TagType.True);
                return new BoolDeclaration(name, true);
            }
            Match(TagType.False);
            return new BoolDeclaration(name, false);
        }

        private IntDeclaration InitializedInt(string name)
        {
            bool negate = false;
            if (m_Look.Tag == '-')
            {
                Match('-');
                negate = true;
            }
            Num token = (Num)m_Look;
            Match(TagType.Num);
            return new IntDeclaration(name, negate ? -token.Value : token.Value);
        }

        private FloatDeclaration InitializedFloat(string name)
        {
            bool negate = false;
            if (m_Look.Tag == '-')
            {
                Match('-');
                negate = true;
            }
            Real token = (Real)m_Look;
            Match(TagType.Real);
            return new FloatDeclaration(name, negate ? -token.Value : token.Value);
        }

        private Declaration UninitializedDeclaration(CType t, string name)
        {
            if (t == CType.Bool)
            {
                return new BoolDeclaration(name);
            }
            else if (t == CType.Int)
            {
                return new IntDeclaration(name);
            }
            else if (t == CType.Float)
            {
                return new FloatDeclaration(name);
            }
            return null;
        }

        private CType Type()
        {
            CType t = (CType)m_Look;
            Match((int)TagType.Basic);
            if (m_Look.Tag != '[')
                return t;
            return Dims(t);
        }

        private CType Dims(CType t)
        {
            throw new NotImplementedException("arrays not implemented");
        }
    }
}
