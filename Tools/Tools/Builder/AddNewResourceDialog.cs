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
using Tools.Models;

namespace Tools.Builder
{
    public partial class AddNewResourceDialog : Form
    {
        public List<Resource> NewResources = new List<Resource>();

        public Sprite NewSprite;

        public AddNewResourceDialog()
        {
            InitializeComponent();
        }

        private void AddNewResourceDialog_Load(object sender, EventArgs e)
        {
        }

        private void btnAddfile_Click(object sender, EventArgs e)
        {
            OpenFileDialog chooseFileDiag = new OpenFileDialog();
            chooseFileDiag.Multiselect = true;

            var res = chooseFileDiag.ShowDialog();

            if(res == DialogResult.OK)
            {
                var files = chooseFileDiag.FileNames.Select(p => new FileInfo(p));

                if(files.Any(p => !p.Exists)) // Check if any files do not exist
                {
                    var badFiles = files.Where(p => !p.Exists);

                    var badFilesString = "Those files do not exist : " + Environment.NewLine + files.Select(p => p.FullName).Aggregate("", (agg, fileName) => { return agg += fileName + Environment.NewLine; });

                    MessageBox.Show(badFilesString);
                }

                NewResources.AddRange(files.Select(p => new Resource() {
                    ResourceFile = p,
                    ResourceFileExtension = p.Extension,
                    ResourceName = p.Name
                }));

                this.DialogResult = DialogResult.OK;
                this.Close();
            }else
            {
                this.DialogResult = res;
                this.Close();
            }
        }

        private void btnAddSprite_Click(object sender, EventArgs e)
        {
            AddNewSpriteDialog diag = new AddNewSpriteDialog();

            diag.ShowDialog();

            if(diag.DialogResult == DialogResult.OK)
            {
                NewSprite = diag.NewSprite;

                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private void btnAddContainer_Click(object sender, EventArgs e)
        {

        }
    }
}
