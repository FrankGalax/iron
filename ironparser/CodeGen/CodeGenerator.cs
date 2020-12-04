using System.Collections.Generic;
using System.Text;
using IronParser.Parsing.Syntax;
using IronParser.CodeGen.Visitors;
using System.IO;
using System;

namespace IronParser.CodeGen
{
    class CodeGenerator
    {
        private Class m_Class;
        private string m_FilePath;

        public CodeGenerator(Class c, string filePath)
        {
            m_Class = c;
            m_FilePath = filePath;
        }

        public void Generate()
        {
            H();
            Cpp();
        }

        private void H()
        {
            string file = File.ReadAllText(m_FilePath.Replace(".iron", ".h")).Replace("\r", "");

            string userCode = "";
            string userCodeNameSpace = "";
            string userCodeClass = "";
            string userCodeEnd = "";

            int userCodeStartIndex = file.IndexOf("#pragma region usercode\n");
            if (userCodeStartIndex != -1)
            {
                int userCodeEndIndex = file.IndexOf("#pragma endregion", userCodeStartIndex);
                userCode = file.Substring(userCodeStartIndex, userCodeEndIndex - userCodeStartIndex + 18);
            }

            int userCodeNamespaceStartIndex = file.IndexOf("#pragma region usercodenamespace");
            if (userCodeNamespaceStartIndex != -1)
            {
                int userCodeNamespaceEndIndex = file.IndexOf("#pragma endregion", userCodeNamespaceStartIndex);
                userCodeNameSpace = file.Substring(userCodeNamespaceStartIndex, userCodeNamespaceEndIndex - userCodeNamespaceStartIndex + 18);
            }

            int userCodeClassStartIndex = file.IndexOf("#pragma region usercodeclass");
            if (userCodeClassStartIndex != -1)
            {
                int userCodeClassEndIndex = file.IndexOf("#pragma endregion", userCodeClassStartIndex);
                userCodeClass = file.Substring(userCodeClassStartIndex, userCodeClassEndIndex - userCodeClassStartIndex + 18);
            }

            int userCodeEndStartIndex = file.IndexOf("#pragma region usercodeend");
            if (userCodeEndStartIndex != -1)
            {
                int userCodeEndEndIndex = file.IndexOf("#pragma endregion", userCodeEndStartIndex);
                userCodeEnd = file.Substring(userCodeEndStartIndex, userCodeEndEndIndex - userCodeEndStartIndex + 17);
            }

            StringBuilder hBuilder = new StringBuilder();
            hBuilder.Append("#pragma once\n\n")
                .Append("#include <iron.h>\n");

            foreach (string include in m_Class.Includes)
            {
                hBuilder.Append("#include <").Append(include).Append(">\n");
            }

            if (!String.IsNullOrEmpty(userCode))
            {
                hBuilder.Append("\n").Append(userCode);
            }

            hBuilder.Append("\n")
                .Append("ironBEGIN_NAMESPACE\n\n");

            hBuilder.Append("class JSON;\n");
            ApplyVisitor(new HForwardDeclareDeclarationVisitor(hBuilder));

            hBuilder.Append("\n");

            if (!String.IsNullOrEmpty(userCodeNameSpace))
            {
                hBuilder.Append(userCodeNameSpace).Append("\n");
            }

            hBuilder.Append("class ")
                .Append(m_Class.Name);

            if (m_Class.ParentClassName != null)
            {
                hBuilder.Append(" : public ")
                    .Append(m_Class.ParentClassName);
            }
            
            hBuilder.Append("\n{\n")
            // public
                .Append("public:\n");

            if (m_Class.HasAttribute("Virtual"))
            {
                hBuilder.Tab().Append("virtual ~").Append(m_Class.Name).Append("() {}\n\n");
            }

            hBuilder.Tab().Append(m_Class.Name).Append("() {}\n");

            bool needConstructor = false;
            foreach (Declaration declaration in m_Class.Declarations)
            {
                if (!declaration.HasAttribute("ConstructorIgnore"))
                {
                    needConstructor = true;
                }
            }

            if (needConstructor)
            {
                // Default Constructor
                bool isDefault = true;
                foreach (Declaration declaration in m_Class.Declarations)
                {
                    if (!declaration.HasDefaultValue())
                    {
                        hBuilder.Tab()
                            .Append(m_Class.Name)
                            .Append("(");
                        ApplyVisitor(new HConstructorParamsDeclarationVisitor(hBuilder, isDefault));
                        hBuilder.Append(") : ");
                        ApplyVisitor(new HConstructorParamsInitDeclarationVisitor(hBuilder, isDefault));
                        hBuilder.Append(" {}\n");
                        break;
                    }
                }

                // Param Constructor
                hBuilder.Tab()
                    .Append(m_Class.Name)
                    .Append("(");
                ApplyVisitor(new HConstructorParamsDeclarationVisitor(hBuilder, !isDefault));
                hBuilder.Append(") : ");
                ApplyVisitor(new HConstructorParamsInitDeclarationVisitor(hBuilder, !isDefault));
                hBuilder.Append(" {}\n\n");
            }

            // Getters and setters
            ApplyVisitor(new HGetterSetterDeclarationVisitor(hBuilder));

            hBuilder.Append("\n");

            hBuilder.Tab();

            if (!String.IsNullOrEmpty(m_Class.ParentClassName) || m_Class.HasAttribute("Virtual"))
            {
                hBuilder.Append("virtual ");
            }

            hBuilder.Append("void ToJSON(JSON* j)");

            if (!String.IsNullOrEmpty(m_Class.ParentClassName))
            {
                hBuilder.Append(" override");
            }
            else if(m_Class.HasAttribute("Virtual"))
            {
                hBuilder.Append(" = 0");
            }
            hBuilder.Append(";\n");

            // private
            hBuilder.Append("\nprivate:\n");
            ApplyVisitor(new HDeclareGenDeclarationVisitor(hBuilder));

            if (!String.IsNullOrEmpty(userCodeClass))
            {
                hBuilder.Append("\n").Append(userCodeClass);
            }

            hBuilder.Append("};\n\n")
                .Append("ironEND_NAMESPACE");

            if (!String.IsNullOrEmpty(userCodeEnd))
            {
                hBuilder.Append("\n\n").Append(userCodeEnd);
            }

            string str = hBuilder.ToString();
            if (!str.Equals(file))
            {
                File.WriteAllText(m_FilePath.Replace(".iron", ".h"), str);
            }
        }

        private void Cpp()
        {
            string file = File.ReadAllText(m_FilePath.Replace(".iron", ".cpp")).Replace("\r", "");

            string userCode = "";
            string userCodeNameSpace = "";

            int userCodeStartIndex = file.IndexOf("#pragma region usercode\n");
            if (userCodeStartIndex != -1)
            {
                int userCodeEndIndex = file.IndexOf("#pragma endregion", userCodeStartIndex);
                userCode = file.Substring(userCodeStartIndex, userCodeEndIndex - userCodeStartIndex + 18);
            }

            int userCodeNamespaceStartIndex = file.IndexOf("#pragma region usercodenamespace");
            if (userCodeNamespaceStartIndex != -1)
            {
                int userCodeNamespaceEndIndex = file.IndexOf("#pragma endregion", userCodeNamespaceStartIndex);
                userCodeNameSpace = file.Substring(userCodeNamespaceStartIndex, userCodeNamespaceEndIndex - userCodeNamespaceStartIndex + 18);
            }

            StringBuilder cppBuilder = new StringBuilder();

            string includePath = m_FilePath.Substring(21).Replace("\\", "/").Replace(".iron", ".h");
            cppBuilder.Append("#include <")
                .Append(includePath)
                .Append(">\n")
                .Append("#include <json.h>\n")
                .Append("\n");

            if (!String.IsNullOrEmpty(userCode))
            {
                cppBuilder.Append(userCode).Append("\n");
            }
            
            cppBuilder.Append("ironBEGIN_NAMESPACE\n\n");

            cppBuilder.Append("void ").Append(m_Class.Name).Append("::ToJSON(JSON* json)\n").Append("{\n");

            cppBuilder.Tab().Append("nlohmann::json& j = json->GetJ();\n");
            cppBuilder.Tab().Append("j[\"class\"] = ").Append(m_Class.Name.GetStableHashCode()).Append(";\n");
            ApplyVisitor(new CPPJSONDeclarationVisitor(cppBuilder));

            cppBuilder.Append("}\n\n");

            if (!String.IsNullOrEmpty(userCodeNameSpace))
            {
                cppBuilder.Append(userCodeNameSpace).Append("\n");
            }

            cppBuilder.Append("ironEND_NAMESPACE");

            string str = cppBuilder.ToString();
            if (!str.Equals(file))
            {
                File.WriteAllText(m_FilePath.Replace(".iron", ".cpp"), str);
            }
        }

        private void ApplyVisitor(DeclarationVisitor visitor)
        {
            foreach (Declaration declaration in m_Class.Declarations)
            {
                declaration.AcceptVisitor(visitor);
            }
        }
    }
}
