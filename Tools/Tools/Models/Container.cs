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
            ContainerName = element.Attribute("name").Value;

            var containerFormatString = element.Attribute("format").Value;

            switch(containerFormatString)
            {
                case "folder":
                    ContainerFormat = ContainerFormats.Folder;
                    ContainerFolder = new DirectoryInfo(Path.Combine(Environment.CurrentDirectory, ContainerName));
                    break;
                case "package":
                    ContainerFormat = ContainerFormats.Package;
                    ContainerPackage = new FileInfo(Path.Combine(Environment.CurrentDirectory, ContainerName + ".pack")); // TODO : Get .pack extension by config or static const
                    break;
            }



        }

        public string ContainerName { get; set; }

        public ContainerFormats ContainerFormat { get; set; }

        DirectoryInfo ContainerFolder { get; set; }

        FileInfo ContainerPackage { get; set; }
    }
}
