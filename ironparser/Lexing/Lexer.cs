using System.Collections.Generic;
using System.Text;

namespace IronParser.Lexing
{
    class Lexer
    {
        public static int Line = 1;

        private string m_Source;
        private int m_Current;
        private char m_Peek;
        private Dictionary<string, Word> m_Words;

        public Lexer(string source)
        {
            m_Source = source;
            m_Current = 0;
            m_Peek = ' ';
            m_Words = new Dictionary<string, Word>();
            Reserve(new Word("true", TagType.True));
            Reserve(new Word("false", TagType.False));
            Reserve(CType.Int);
            Reserve(CType.Bool);
            Reserve(CType.Float);
            Reserve(new Word("class", TagType.Class));
        }

        private void Reserve(Word word)
        {
            m_Words.Add(word.Lexeme, word);
        }

        private void Readch()
        {
            m_Peek = m_Source[m_Current];
            if (m_Current + 1 < m_Source.Length)
                m_Current++;
        }

        private bool Readch(char c)
        {
            Readch();
            if (m_Peek != c)
                return false;
            m_Peek = ' ';
            return true;
        }

        public Token Scan()
        {
            for (; ; Readch())
            {
                // line comments
                if (m_Peek == '/' && m_Source[m_Current] == '/')
                {
                    do
                    {
                        Readch();
                    } while (m_Peek != '\n');
                }

                // white spaces
                if (m_Peek == ' ' || m_Peek == '\t' || m_Peek == '\r')
                    continue;

                // new lines
                if (m_Peek == '\n')
                    Line += 1;
                else
                    break;
            }

            if (char.IsDigit(m_Peek))
            {
                int v = 0;
                do
                {
                    v = 10 * v + (m_Peek - '0');
                    Readch();
                } while (char.IsDigit(m_Peek));
                if (m_Peek != '.')
                    return new Num(v);
                float x = v;
                float d = 10;
                for (;;)
                {
                    Readch();
                    if (!char.IsDigit(m_Peek))
                        break;
                    x = x + (m_Peek - '0') / d;
                    d = d * 10;
                }
                if (m_Peek == 'f')
                    Readch();
                return new Real(x);
            }
            else if (char.IsLetter(m_Peek))
            {
                StringBuilder b = new StringBuilder();
                do
                {
                    b.Append(m_Peek);
                    Readch();
                } while (char.IsLetterOrDigit(m_Peek));
                string s = b.ToString();

                if (m_Words.ContainsKey(s))
                    return m_Words[s];

                Word w = new Word(s, TagType.Id);
                m_Words.Add(s, w);
                return w;
            }
            Token tok = new Token((int)m_Peek);
            m_Peek = ' ';
            return tok;
        }
    }
}
