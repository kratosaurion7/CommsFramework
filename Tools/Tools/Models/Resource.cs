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
            if (element.Attribute("name") != null)
                ResourceName = element.Attribute("name").Value;

            if (element.Attribute("type") != null)
                ResourceType = element.Attribute("type").Value;

            if (element.Attribute("format") != null)
                ResourceFileExtension = element.Attribute("format").Value; 

            ResourceFile = new FileInfo(ResourceName); // TODO : REmove the extension from the res name and append the res type here
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
