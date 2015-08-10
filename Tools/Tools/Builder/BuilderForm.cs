using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using Tools.Framework;
using Tools.Models;

namespace Tools.Builder
{
    public enum OutputFormat
    {
        Package,
        Folder
    }

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
            FolderBrowserDialog folderDiag = new FolderBrowserDialog();
            folderDiag.ShowNewFolderButton = true;
            folderDiag.RootFolder = Environment.SpecialFolder.MyComputer;
            folderDiag.Description = "Choose destination for the build.";

            var res = folderDiag.ShowDialog();

            if(res == DialogResult.OK)
            {
                var filesToSave = GetCurrentAssetFiles();
                var directory = new DirectoryInfo(folderDiag.SelectedPath);
                var format = rdbPackageFile.Checked == true ? OutputFormat.Package : OutputFormat.Folder;

                bool saveSuccess = SaveAssetsAndConfig(filesToSave, directory, format);

                if(saveSuccess)
                {
                    MessageBox.Show("Success !");
                }
                else
                {
                    MessageBox.Show("Failure !");
                }
            }
        }

        public IEnumerable<FileInfo> GetCurrentAssetFiles()
        {
            var files = ConfigMappings
                .SelectMany(p => p.Value.CurrentConfig.Resources
                                                      .Select(t => t.ResourceFile)
                                                      .Concat(p.Value.CurrentConfig.Sprites
                                                                                   .SelectMany(q => q.SpriteFrames))
                );

            return files;
        }

        public bool SaveAssetsAndConfig(IEnumerable<FileInfo> inputFiles, DirectoryInfo outputFolder, OutputFormat saveFormat)
        {
            var configs = ConfigMappings.Select(p => p.Value.CurrentConfig);

            var rootConfig = configs.First();

            bool success = true;

            foreach (var item in configs)
            {
                XElement configFile = SerializeBuilderConfig(item);

                try
                {
                    configFile.Save(Path.Combine(outputFolder.FullName, item.ConfigName + ".xml"));
                }
                catch (Exception)
                {
                    success = false;
                }
            }

            if (saveFormat == OutputFormat.Folder)
            {
                try
                {
                    foreach (var item in inputFiles)
                    {
                        item.CopyTo(Path.Combine(outputFolder.FullName, item.Name), true);
                    }
                }
                catch (Exception)
                {
                    success = false;
                }

            }
            else if (saveFormat == OutputFormat.Package)
            {
                try
                {
                    PAKFile package = new PAKFile();
                    package.AddFiles(inputFiles);

                    package.Save(new FileInfo(Path.Combine(outputFolder.FullName, "package.pak")));
                }
                catch (Exception)
                {
                    success = false;
                }

            }

            return success;
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
