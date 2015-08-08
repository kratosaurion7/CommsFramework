using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools.Models
{
    public class Resource
    {
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
