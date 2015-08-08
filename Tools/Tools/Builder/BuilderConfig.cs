using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tools.Models;

namespace Tools.Builder
{
    public class BuilderConfig
    {
        public string ConfigName { get; set; }

        public List<Resource> Resources = new List<Resource>();

        public List<Sprite> Sprites = new List<Sprite>();
    }
}
