using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tools.Models;

namespace Tools.Builder
{
    public partial class BuilderForm : Form
    {
        private BuilderConfig _CurrentConfig;

        public BuilderForm()
        {
            InitializeComponent();

            _CurrentConfig = new BuilderConfig();

            
        }

        private void BuilderForm_Load(object sender, EventArgs e)
        {

        }

        private Panel CreateResourcePanelForResource()
        {
            var pnl = new TableLayoutPanel();

            pnl.AutoSize = true;
            

            pnl.Controls.Add(new Label() { Text = "Resource : " , AutoSize = true}, 0, 0);
            pnl.Controls.Add(new TextBox() { Text = "buttan", Dock = DockStyle.Fill, AutoSize = true }, 1, 0);
            pnl.Controls.Add(new TextBox() { Text = "buttan2", Dock = DockStyle.Fill, AutoSize = true }, 2, 0);
            pnl.Controls.Add(new TextBox() { Text = "lol", ForeColor = Color.OrangeRed, Dock = DockStyle.Fill, AutoSize = true }, 3, 0);
            pnl.Controls.Add(new CheckBox() { Checked = false, Dock = DockStyle.Fill }, 4, 0);

            pnl.Height = 25;
            pnl.Width = 400;

            return pnl;
        }

        public void AddResourceToList(Resource res)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            AddNewResourceDialog newResDialog = new AddNewResourceDialog();

            newResDialog.ShowDialog();

            if(newResDialog.DialogResult == DialogResult.OK)
            {
                foreach (var item in newResDialog.NewResources)
                {
                    _CurrentConfig.Resources.Add(item);

                    resourcesListbox.Items.Add(item);
                }

                if(newResDialog.NewSprite != null)
                {
                    _CurrentConfig.Sprites.Add(newResDialog.NewSprite);

                    resourcesListbox.Items.Add(newResDialog.NewSprite);
                }

            }

            selectAllCheckbox.Checked = false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var itemsToDelete = new List<object>();

            foreach (var box in resourcesListbox.CheckedItems)
            {
                if (box is Resource)
                {
                    var boxItem = box as Resource;

                    _CurrentConfig.Resources.Remove(boxItem);

                }

                if(box is Sprite)
                {
                    var boxItem = box as Sprite;

                    _CurrentConfig.Sprites.Remove(boxItem);
                }

                itemsToDelete.Add(box);
            }

            itemsToDelete.ForEach(p => resourcesListbox.Items.Remove(p));

            selectAllCheckbox.Checked = false;
        }

        private void selectAllCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            for(int i = 0; i < resourcesListbox.Items.Count; i++)
            {
                resourcesListbox.SetItemChecked(i, selectAllCheckbox.Checked);
            }
        }
    }
}
