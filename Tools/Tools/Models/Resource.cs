using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Tools.Models
{
    public class Resource
    {
        public Resource()
        {

        }

        public Resource(XElement element)
        {
            ResourceName = element.Attribute("name").Value;
            ResourceType = element.Attribute("type").Value;
            ResourceFileExtension = element.Attribute("format").Value;

            ResourceFile = null;
        }

        public FileInfo ResourceFile;

        public string ResourceName;

        public string ResourceType;

        public string ResourceFileExtension;

        public override string ToString()
        {
            return ResourceName + " " + ResourceType + " " + ResourceFileExtension;
        }
    }
}
