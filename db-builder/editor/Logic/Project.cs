using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class Project: IDisposable
    {
        #region Properties
        private String filename;
        public String Filename
        {
            get
            {
                return filename;
            }
            set
            {
                filename = value;
            }
        }
        private String name;
        public String Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }
        private int version = 1;
        public int Version
        {
            get
            {
                return version;
            }
            set
            {
                version = value;
            }
        }
        private List<Page> pages;
        public ICollection<Page> Pages
        {
            get
            {
                return pages;
            }
        }
        #endregion

        #region Constructors
        public Project()
        {
            pages = new List<Page>();
        }
        #endregion

        #region Public Methods
        public void Dispose()
        {
            foreach (Page page in pages)
                page.Dispose();
        }
        public XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("project");
            XmlElement version = doc.CreateElement("version");
            version.InnerText = Version.ToString();
            root.AppendChild(version);
            XmlElement name = doc.CreateElement("name");
            name.InnerText = Name;
            root.AppendChild(name);

            foreach (Page page in Pages)
            {
                root.AppendChild(page.ToXmlElement(doc));
            }

            return root;
        }
        public void FromXmlElement(XmlElement root)
        {
            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "version")
                    Version = int.Parse(node.InnerText);
                if (node.Name == "name")
                    Name = node.InnerText;
                else if (node.Name == "page")
                {
                    Page page = new Page();
                    page.FromXmlElement((XmlElement)node);
                    Pages.Add(page);
                }
            }
        }
        #endregion
    }
}
