using System.Collections.Generic;
using System;
using IronParser.Lexing;
using IronParser.Parsing.Syntax;

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
            List<FieldAttribute> attrs = new List<FieldAttribute>();
            while (m_Look.Tag == '[')
            {
                List<FieldAttribute> fieldAttributes = FieldAttributes();
                attrs.AddRange(fieldAttributes);
            }

            Match(TagType.Class);
            Class c = new Class
            {
                Name = ((Word)m_Look).Lexeme,
                Attributes = attrs,
                Includes = new List<string>()
            };
            Match(TagType.Id);

            if (m_Look.Tag == ':')
            {
                Match(':');
                c.ParentClassName = ((Word)m_Look).Lexeme;
                Match(TagType.Id);
            }

            Match('{');
            c.Declarations = Declarations();
            Match('}');

            if (c.ParentClassName != null && c.ParentClassName.Equals("Component"))
            {
                c.Includes.Add("ecs/component.h");
            }

            bool addedVector = false;
            bool addedString = false;
            bool addedStdVector = false;
            foreach (Declaration declaration in c.Declarations)
            {
                if (declaration is Vector2fDeclaration && !addedVector)
                {
                    c.Includes.Add("math/vector.h");
                    addedVector = true;
                }

                if (declaration is StringDeclaration && !addedString)
                {
                    c.Includes.Add("string");
                    addedString = true;
                }

                if (declaration.IsArray && !addedStdVector)
                {
                    c.Includes.Add("vector");
                }
            }
            return c;
        }

        public List<Declaration> Declarations()
        {
            List<Declaration> declarations = new List<Declaration>();

            while (m_Look.Tag == (int)TagType.Const ||
                m_Look.Tag == (int)TagType.Basic || 
                m_Look.Tag == (int)TagType.Id || 
                m_Look.Tag == '[')
            {
                Declaration decl = Declaration();
                Match(';');
                declarations.Add(decl);
            }
            return declarations;
        }

        private Declaration Declaration()
        {
            List<FieldAttribute> attrs = new List<FieldAttribute>();
            while (m_Look.Tag == '[')
            {
                List<FieldAttribute> fieldAttributes = FieldAttributes();
                attrs.AddRange(fieldAttributes);
            }

            TypeInfo typeInfo = new TypeInfo();

            if (m_Look.Tag == (int)TagType.Const)
            {
                typeInfo.IsConst = true;
                Match(TagType.Const);
            }

            CType t = Type();

            if (m_Look.Tag == '*')
            {
                typeInfo.IsPointer = true;
                Match('*');
            }

            if (m_Look.Tag == '[')
            {
                typeInfo.IsArray = true;
                Match('[');
                Match(']');
            }

            Word word = (Word)m_Look;
            Match(TagType.Id);
            Declaration decl = null;

            if (m_Look.Tag == '=')
            {
                decl = InitializedDeclaration(t, word.Lexeme, typeInfo);
            }
            else
            {
                if (t.Tag == (int)TagType.Custom)
                {
                    decl = new CustomDeclaration(word.Lexeme, t.Lexeme, typeInfo);
                }
                else
                {
                    decl = UninitializedDeclaration(t, word.Lexeme, typeInfo);
                }
            }

            if (decl == null)
            {
                Error("invalid declaration");
            }
            decl.Attributes = attrs;
            return decl;
        }

        private List<FieldAttribute> FieldAttributes()
        {
            List<FieldAttribute> declarationAttributes = new List<FieldAttribute>();
            Match('[');
            do
            {
                if (m_Look.Tag == ',')
                {
                    Match(',');
                }
                declarationAttributes.Add(new FieldAttribute { Name = ((Word)m_Look).Lexeme });
                Match(TagType.Id);
            } while (m_Look.Tag == ',');

            Match(']');

            return declarationAttributes;
        }

        private Declaration InitializedDeclaration(CType t, string name, TypeInfo typeInfo)
        {
            Match('=');
            if (t == CType.Bool)
            {
                return InitializedBool(name, typeInfo);
            }
            else if (t == CType.Int)
            {
                return InitializedInt(name, typeInfo);
            }
            else if (t == CType.Float)
            {
                return InitializedFloat(name, typeInfo);
            }
            else if (t == CType.Vector2f)
            {
                return InitializedVector2f(name, typeInfo);
            }
            else if (t == CType.String)
            {
                return InitializedString(name, typeInfo);
            }
            return null;
        }

        private BoolDeclaration InitializedBool(string name, TypeInfo typeInfo)
        {
            if (m_Look.Tag == (int)TagType.True)
            {
                Match(TagType.True);
                return new BoolDeclaration(name, true, typeInfo);
            }
            Match(TagType.False);
            return new BoolDeclaration(name, false, typeInfo);
        }

        private IntDeclaration InitializedInt(string name, TypeInfo typeInfo)
        {
            bool negate = false;
            if (m_Look.Tag == '-')
            {
                Match('-');
                negate = true;
            }
            Num token = (Num)m_Look;
            Match(TagType.Num);
            return new IntDeclaration(name, negate ? -token.Value : token.Value, typeInfo);
        }

        private FloatDeclaration InitializedFloat(string name, TypeInfo typeInfo)
        {
            bool negate = false;
            if (m_Look.Tag == '-')
            {
                Match('-');
                negate = true;
            }
            Real token = (Real)m_Look;
            Match(TagType.Real);
            return new FloatDeclaration(name, negate ? -token.Value : token.Value, typeInfo);
        }

        private Vector2fDeclaration InitializedVector2f(string name, TypeInfo typeInfo)
        {
            Real xToken = (Real)m_Look;
            Match(TagType.Real);
            Match(',');
            Real yToken = (Real)m_Look;
            Match(TagType.Real);
            return new Vector2fDeclaration(name, xToken.Value, yToken.Value, typeInfo);
        }

        private StringDeclaration InitializedString(string name, TypeInfo typeInfo)
        {
            Match('"');
            string value = ((Word)m_Look).Lexeme;
            Match(TagType.Id);
            Match('"');
            return new StringDeclaration(name, value, typeInfo);
        }

        private Declaration UninitializedDeclaration(CType t, string name, TypeInfo typeInfo)
        {
            if (t == CType.Bool)
            {
                return new BoolDeclaration(name, typeInfo);
            }
            else if (t == CType.Int)
            {
                return new IntDeclaration(name, typeInfo);
            }
            else if (t == CType.Float)
            {
                return new FloatDeclaration(name, typeInfo);
            }
            else if (t == CType.Vector2f)
            {
                return new Vector2fDeclaration(name, typeInfo);
            }
            else if (t == CType.String)
            {
                return new StringDeclaration(name, typeInfo);
            }

            return null;
        }

        private CType Type()
        {
            CType t = null;
            if (m_Look is CType)
            {
                t = (CType)m_Look;
                Match((int)TagType.Basic);
            }
            else if (m_Look is Word)
            {
                t = new CType(((Word)m_Look).Lexeme, TagType.Custom);
                Match(m_Look.Tag);
            }

            if (t == null)
            {
                Error("unrecognized type");
            }

            return t;
        }
    }
}
