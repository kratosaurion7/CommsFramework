using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Tools.Models
{
    public enum ContainerFormats
    {
        Package,
        Folder
    }

    public class Container
    {
        public Container()
        {

        }

        public Container(XElement element)
        {
            if(element.Attribute("name") != null)
                ContainerName = element.Attribute("name").Value;

            if(element.Attribute("format") != null)
            {
                var containerFormatString = element.Attribute("format").Value;

                switch (containerFormatString)
                {
                    case "folder":
                        ContainerFormat = ContainerFormats.Folder;
                        ContainerFolder = new DirectoryInfo(ContainerName);
                        break;
                    case "package":
                        ContainerFormat = ContainerFormats.Package;
                        ContainerPackage = new FileInfo(ContainerName + ".pack"); // TODO : Get .pack extension by config or static const
                        break;
                }
            }else
            {
                // Default case is package.
                ContainerFormat = ContainerFormats.Package;
                ContainerPackage = new FileInfo(ContainerName + ".pack"); // TODO : Get .pack extension by config or static const
            }
        }

        public string ContainerName { get; set; }

        public ContainerFormats ContainerFormat { get; set; }

        DirectoryInfo ContainerFolder { get; set; }

        FileInfo ContainerPackage { get; set; }
    }
}
