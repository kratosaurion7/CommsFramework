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
    public partial class AddNewSpriteDialog : Form
    {
        public Sprite NewSprite = new Sprite();

        public AddNewSpriteDialog()
        {
            InitializeComponent();
        }

        private void btnChooseFrames_Click(object sender, EventArgs e)
        {
            OpenFileDialog diag = new OpenFileDialog();
            diag.Multiselect = true;
            var res = diag.ShowDialog();

            if (res == DialogResult.OK)
            {
                framesListbox.Items.Clear();

                NewSprite.SpriteFrames = diag.FileNames.Select(p => new FileInfo(p));

                var imageFiles = NewSprite.SpriteFrames.Where(p => p.Extension == ".png" || p.Extension == ".jpg");

                foreach (var item in imageFiles)
                {
                    framesListbox.Items.Add(item.Name);
                }
            }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            NewSprite.SpriteName = txtSpriteName.Text;
            NewSprite.GameModule = txtGameModule.Text;

            if (!String.IsNullOrWhiteSpace(txtPositionX.Text))
                NewSprite.PositionX = int.Parse(txtPositionX.Text);

            if (!String.IsNullOrWhiteSpace(txtPositionY.Text))
                NewSprite.PositionY = int.Parse(txtPositionY.Text);

            if (!String.IsNullOrWhiteSpace(txtSizeHeight.Text))
                NewSprite.Height = int.Parse(txtSizeHeight.Text);

            if (!String.IsNullOrWhiteSpace(txtSizeWidth.Text))
                NewSprite.Width = int.Parse(txtSizeWidth.Text);

            DialogResult = DialogResult.OK;
            this.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
