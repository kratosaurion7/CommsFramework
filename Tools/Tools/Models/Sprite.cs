using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools.Models
{
    public class Sprite
    {
        public string SpriteName;

        public string GameModule;

        public int PositionX;
        public int PositionY;

        public int Height;
        public int Width;
        
        public IEnumerable<FileInfo> SpriteFrames = new List<FileInfo>();

        public override string ToString()
        {
            return SpriteName + " x" + SpriteFrames.Count().ToString() + " frames";
        }
    }
}
