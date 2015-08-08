using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using Tools.Models;

namespace Tools.Builder
{
    public partial class BuilderForm : Form
    {
        public Dictionary<TabPage, AddConfigControls> ConfigMappings = new Dictionary<TabPage, AddConfigControls>();

        public BuilderForm()
        {
            InitializeComponent();
        }

        private void BuilderForm_Load(object sender, EventArgs e)
        {
            var rootPage = CreateNewConfigTabPage();

            

            configTabControl.TabPages.Add(rootPage);
        }

        public TabPage CreateNewConfigTabPage()
        {
            AddConfigControls newTabContents = new AddConfigControls();

            TabPage newPage = new TabPage();
            newPage.Controls.Add(newTabContents);
            newPage.BackColor = Color.White;

            newPage.Text = "Config";

            newTabContents.ParentPage = newPage;

            ConfigMappings.Add(newPage, newTabContents);

            return newPage;
        }

        private void btnAddConfig_Click(object sender, EventArgs e)
        {
            configTabControl.TabPages.Add(CreateNewConfigTabPage());
        }

        private void btnSaveConfig_Click(object sender, EventArgs e)
        {
            var configs = ConfigMappings.Select(p => p.Value.CurrentConfig);

            var rootConfig = configs.First();

            foreach (var item in configs)
            {
                XElement configFile = SerializeBuilderConfig(item);

                configFile.Save(item.ConfigName + ".xml");
            }
        }

        public XElement SerializeBuilderConfig(BuilderConfig config)
        {
            XElement configNode = new XElement("config");

            foreach (var res in config.Resources)
            {
                XElement resourceNode = new XElement("resource");
                resourceNode.SetAttributeValue("name", res.ResourceName);
                resourceNode.SetAttributeValue("type", res.ResourceType);
                resourceNode.SetAttributeValue("format", res.ResourceFileExtension);

                configNode.Add(resourceNode);
            }

            foreach (var sprite in config.Sprites)
            {
                XElement spriteElement = new XElement("sprite");
                spriteElement.SetAttributeValue("name", sprite.SpriteName);
                spriteElement.SetAttributeValue("module", sprite.GameModule);

                XElement posNode = new XElement("position");
                posNode.SetAttributeValue("X", sprite.PositionX);
                posNode.SetAttributeValue("Y", sprite.PositionY);

                XElement sizeNode = new XElement("size");
                sizeNode.SetAttributeValue("Height", sprite.Height);
                sizeNode.SetAttributeValue("Width", sprite.Width);

                spriteElement.Add(posNode);

                spriteElement.Add(sizeNode);

                XElement framesRoot = new XElement("frames");

                foreach (var frame in sprite.SpriteFramesResources)
                {
                    XElement frameNode = new XElement("frame");
                    frameNode.SetAttributeValue("Id", frame.ResourceName);


                    spriteElement.Add(frameNode);

                    // Make sure to add a resource entry to the main config node for each frame added.
                    XElement resourceNode = new XElement("resource");
                    resourceNode.SetAttributeValue("name", frame.ResourceName);
                    resourceNode.SetAttributeValue("type", frame.ResourceType);
                    resourceNode.SetAttributeValue("format", frame.ResourceFileExtension);

                    configNode.Add(resourceNode);
                }

                configNode.Add(spriteElement);
            }

            return configNode;
        }

        private void btnRemoveConfig_Click(object sender, EventArgs e)
        {
            ConfigMappings.Remove(configTabControl.SelectedTab);

            configTabControl.TabPages.RemoveAt(configTabControl.SelectedIndex);
        }
    }
}
