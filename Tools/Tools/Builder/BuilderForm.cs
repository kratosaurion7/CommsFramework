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
            configTabControl.TabPages.Add(CreateNewConfigTabPage());
        }

        public TabPage CreateNewConfigTabPage()
        {
            AddConfigControls newTabContents = new AddConfigControls();

            TabPage newPage = new TabPage();
            newPage.Controls.Add(newTabContents);
            newPage.BackColor = Color.White;

            newPage.Text = "Config";

            newTabContents.ParentPage = newPage;

            return newPage;
        }

        private void btnAddConfig_Click(object sender, EventArgs e)
        {
           
            configTabControl.TabPages.Add(CreateNewConfigTabPage());
        }
    }
}
