namespace Tools.Builder
{
    partial class AddConfigControls
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.selectAllCheckbox = new System.Windows.Forms.CheckBox();
            this.resourcesListbox = new System.Windows.Forms.CheckedListBox();
            this.btnNewResource = new System.Windows.Forms.Button();
            this.btnRemoveResource = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.txtConfigName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // selectAllCheckbox
            // 
            this.selectAllCheckbox.AutoSize = true;
            this.selectAllCheckbox.Location = new System.Drawing.Point(10, 69);
            this.selectAllCheckbox.Name = "selectAllCheckbox";
            this.selectAllCheckbox.Size = new System.Drawing.Size(37, 17);
            this.selectAllCheckbox.TabIndex = 14;
            this.selectAllCheckbox.Text = "All";
            this.selectAllCheckbox.UseVisualStyleBackColor = true;
            this.selectAllCheckbox.CheckedChanged += new System.EventHandler(this.selectAllCheckbox_CheckedChanged);
            // 
            // resourcesListbox
            // 
            this.resourcesListbox.CheckOnClick = true;
            this.resourcesListbox.FormattingEnabled = true;
            this.resourcesListbox.Location = new System.Drawing.Point(6, 92);
            this.resourcesListbox.Name = "resourcesListbox";
            this.resourcesListbox.Size = new System.Drawing.Size(450, 184);
            this.resourcesListbox.TabIndex = 13;
            // 
            // btnNewResource
            // 
            this.btnNewResource.Location = new System.Drawing.Point(300, 69);
            this.btnNewResource.Name = "btnNewResource";
            this.btnNewResource.Size = new System.Drawing.Size(75, 23);
            this.btnNewResource.TabIndex = 12;
            this.btnNewResource.Text = "New";
            this.btnNewResource.UseVisualStyleBackColor = true;
            this.btnNewResource.Click += new System.EventHandler(this.btnNewResource_Click);
            // 
            // btnRemoveResource
            // 
            this.btnRemoveResource.Location = new System.Drawing.Point(381, 69);
            this.btnRemoveResource.Name = "btnRemoveResource";
            this.btnRemoveResource.Size = new System.Drawing.Size(75, 23);
            this.btnRemoveResource.TabIndex = 11;
            this.btnRemoveResource.Text = "Remove";
            this.btnRemoveResource.UseVisualStyleBackColor = true;
            this.btnRemoveResource.Click += new System.EventHandler(this.btnRemoveResource_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(4, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Resources :";
            // 
            // txtConfigName
            // 
            this.txtConfigName.Location = new System.Drawing.Point(76, 4);
            this.txtConfigName.Name = "txtConfigName";
            this.txtConfigName.Size = new System.Drawing.Size(182, 20);
            this.txtConfigName.TabIndex = 9;
            this.txtConfigName.TextChanged += new System.EventHandler(this.txtConfigName_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Config name";
            // 
            // AddConfigControls
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.selectAllCheckbox);
            this.Controls.Add(this.resourcesListbox);
            this.Controls.Add(this.btnNewResource);
            this.Controls.Add(this.btnRemoveResource);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtConfigName);
            this.Controls.Add(this.label1);
            this.Name = "AddConfigControls";
            this.Size = new System.Drawing.Size(470, 295);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox selectAllCheckbox;
        private System.Windows.Forms.CheckedListBox resourcesListbox;
        private System.Windows.Forms.Button btnNewResource;
        private System.Windows.Forms.Button btnRemoveResource;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtConfigName;
        private System.Windows.Forms.Label label1;
    }
}
