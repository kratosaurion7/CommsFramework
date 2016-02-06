using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

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
        
        public List<FileInfo> SpriteFrames = new List<FileInfo>();

        public List<Resource> SpriteFramesResources = new List<Resource>();

        public Sprite()
        {

        }

        public Sprite(XElement element)
        {
            if (element.Attribute("name") != null)
                SpriteName = element.Attribute("name").Value; 
            
            if(element.Attribute("module") != null)
                GameModule = element.Attribute("module").Value;

            if (element.Element("position") != null)
            {
                var positionElement = element.Element("position");

                if (positionElement.Attribute("X") != null)
                    PositionX = int.Parse(positionElement.Attribute("X").Value); 
                
                if(positionElement.Attribute("Y") != null)
                    PositionY = int.Parse(positionElement.Attribute("Y").Value);
            }

            if(element.Element("size") != null)
            {
                var sizeElement = element.Element("size");

                if(sizeElement.Element("Height") != null)
                    Height = int.Parse(sizeElement.Element("Height").Value);

                if(sizeElement.Element("Width") != null)
                    Width = int.Parse(sizeElement.Element("Width").Value);
            }

            if (element.Element("frames") != null)
            {
                var framesContainerElement = element.Element("frames");
                foreach (var frameElement in framesContainerElement.Elements("frame"))
                {
                    FileInfo frameFile = new FileInfo(frameElement.Attribute("Id").Value);

                    SpriteFrames.Add(frameFile);
                }

            }
        }

        public override string ToString()
        {
            return SpriteName + " x" + SpriteFrames.Count().ToString() + " frames";
        }
    }
}
