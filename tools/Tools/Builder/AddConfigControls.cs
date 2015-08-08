using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tools.Models;

namespace Tools.Builder
{
    public partial class AddConfigControls : UserControl
    {
        public BuilderConfig CurrentConfig;

        public TabPage ParentPage;

        public AddConfigControls()
        {
            InitializeComponent();

            CurrentConfig = new BuilderConfig();
        }

        private void selectAllCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            for (int i = 0; i < resourcesListbox.Items.Count; i++)
            {
                resourcesListbox.SetItemChecked(i, selectAllCheckbox.Checked);
            }
        }

        private void btnRemoveResource_Click(object sender, EventArgs e)
        {
            var itemsToDelete = new List<object>();

            foreach (var box in resourcesListbox.CheckedItems)
            {
                if (box is Resource)
                {
                    var boxItem = box as Resource;

                    CurrentConfig.Resources.Remove(boxItem);

                }

                if (box is Sprite)
                {
                    var boxItem = box as Sprite;

                    CurrentConfig.Sprites.Remove(boxItem);
                }

                itemsToDelete.Add(box);
            }

            itemsToDelete.ForEach(p => resourcesListbox.Items.Remove(p));

            selectAllCheckbox.Checked = false;
        }

        private void btnNewResource_Click(object sender, EventArgs e)
        {
            AddNewResourceDialog newResDialog = new AddNewResourceDialog();

            newResDialog.ShowDialog();

            if (newResDialog.DialogResult == DialogResult.OK)
            {
                foreach (var item in newResDialog.NewResources)
                {
                    CurrentConfig.Resources.Add(item);

                    resourcesListbox.Items.Add(item);
                }

                if (newResDialog.NewSprite != null)
                {
                    CurrentConfig.Sprites.Add(newResDialog.NewSprite);

                    resourcesListbox.Items.Add(newResDialog.NewSprite);
                }

            }

            selectAllCheckbox.Checked = false;
        }

        private void txtConfigName_TextChanged(object sender, EventArgs e)
        {
            if (ParentPage != null)
                ParentPage.Text = txtConfigName.Text;

            if (CurrentConfig != null)
                CurrentConfig.ConfigName = txtConfigName.Text;

        }
    }
}
