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

        public TabPage CreateNewConfigTabPage(BuilderConfig config)
        {
            AddConfigControls newTabContents = new AddConfigControls(config);

            TabPage newPage = new TabPage();
            newPage.Controls.Add(newTabContents);
            newPage.BackColor = Color.White;

            newPage.Text = config.ConfigName;

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

                if(item == configs.First()) // First config is the root config file, all links to sub configs
                {
                    var subConfigNames = configs.Where(p => p != item).Select(p => p.ConfigName);

                    foreach (var subConfig in subConfigNames)
                    {
                        var configFileElement = new XElement("configFile");
                        configFileElement.Add(new XAttribute("path", subConfig + ".xml")); // TODO : Add extension type by config

                        configFile.Add(configFileElement);
                    }
                }

                try
                {
                    var fileName = item.ConfigName;

                    if(string.IsNullOrWhiteSpace(fileName))
                        fileName = "rootConfig";

                    configFile.Save(Path.Combine(outputFolder.FullName, fileName + ".xml"));
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
            if(!string.IsNullOrWhiteSpace(config.ConfigName))
                configNode.Add(new XAttribute("name", config.ConfigName));

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

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog diag = new OpenFileDialog();

            diag.CheckFileExists = true;
            diag.DefaultExt = ".xml";
            diag.Multiselect = false;
            diag.Title = "Select the root xml file.";
            var result = diag.ShowDialog();

            if(result == DialogResult.OK)
            {
                configTabControl.TabPages.Clear();
                ConfigMappings.Clear();
                FileInfo inputFilename = new FileInfo(diag.FileName);

                if (!inputFilename.Exists)
                {
                    MessageBox.Show("Cannot find " + inputFilename.FullName);
                    return;
                }

                var builderConfigs = CreateBuilderConfigFromFile(inputFilename);

                foreach (var config in builderConfigs)
                {
                    var newTab = CreateNewConfigTabPage(config);

                    configTabControl.TabPages.Add(newTab);
                }
            }
        }

        public List<BuilderConfig> CreateBuilderConfigFromFile(FileInfo configFile)
        {
            List<BuilderConfig> configs = new List<BuilderConfig>();

            BuilderConfig newConfig = new BuilderConfig();

            XElement element = XElement.Load(configFile.FullName, LoadOptions.None);

            if (element.Attribute("name") != null)
            {
                newConfig.ConfigName = element.Attribute("name").Value;
            }

            var resources = GetResourcesOfConfigFile(element);
            var containers = GetContainersOfConfigFile(element);
            var subConfigs = GetSubConfifFiles(element, configFile.Directory);
            var sprites = GetSpritesOfConfigFile(element);

            newConfig.Resources = resources.ToList();
            newConfig.Sprites = sprites.ToList();

            configs.Add(newConfig);

            foreach (var sub in subConfigs)
            {
                var newConfigs = CreateBuilderConfigFromFile(sub);

                configs.AddRange(newConfigs);
            }

            return configs;
        }

        private IEnumerable<Resource> GetResourcesOfConfigFile(XElement configElement)
        {
            return configElement.Elements().Where(p => p.Name == "resource").Select(p => new Resource(p));
        }

        private IEnumerable<Models.Container> GetContainersOfConfigFile(XElement configElement)
        {
            return configElement.Elements().Where(p => p.Name == "config").Select(p => new Models.Container(p));
        }

        private IEnumerable<FileInfo> GetSubConfifFiles(XElement configElement, DirectoryInfo assetDirectory)
        {
            return configElement.Elements().Where(p => p.Name == "configFile").Select(p => new FileInfo(Path.Combine(assetDirectory.FullName, p.Attribute("path").Value)));
        }

        private IEnumerable<Sprite> GetSpritesOfConfigFile(XElement configElement)
        {
            return configElement.Elements().Where(p => p.Name == "sprite").Select(p => new Sprite(p));
        }
    }
}