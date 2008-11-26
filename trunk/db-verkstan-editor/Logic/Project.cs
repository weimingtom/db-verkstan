using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class Project
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
        private int bpm = 120;
        public int BPM
        {
            get
            {
                return bpm;
            }
            set
            {
                bpm = value;
            }
        }   
        private List<OperatorPage> operatorPages;
        public ICollection<OperatorPage> OperatorPages
        {
            get
            {
                return operatorPages;
            }
        }
        #endregion

        #region Constructors
        public Project()
        {
            operatorPages = new List<OperatorPage>();
        }
        #endregion

        #region Public Methods
        public XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("project");
            XmlElement versionElement = doc.CreateElement("version");
            versionElement.InnerText = version.ToString();
            root.AppendChild(versionElement);
            XmlElement bpmElement = doc.CreateElement("bpm");
            bpmElement.InnerText = bpm.ToString();
            root.AppendChild(bpmElement);

            foreach (OperatorPage page in operatorPages)
                root.AppendChild(page.ToXmlElement(doc));

            return root;
        }
        #endregion
    }
}
