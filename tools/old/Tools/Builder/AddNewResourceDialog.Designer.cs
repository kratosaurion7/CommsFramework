namespace Tools.Builder
{
    partial class AddNewResourceDialog
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnAddfile = new System.Windows.Forms.Button();
            this.btnAddSprite = new System.Windows.Forms.Button();
            this.btnAddContainer = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnAddfile
            // 
            this.btnAddfile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAddfile.Location = new System.Drawing.Point(13, 13);
            this.btnAddfile.Name = "btnAddfile";
            this.btnAddfile.Size = new System.Drawing.Size(161, 23);
            this.btnAddfile.TabIndex = 0;
            this.btnAddfile.Text = "Add Files";
            this.btnAddfile.UseVisualStyleBackColor = true;
            this.btnAddfile.Click += new System.EventHandler(this.btnAddfile_Click);
            // 
            // btnAddSprite
            // 
            this.btnAddSprite.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAddSprite.Location = new System.Drawing.Point(13, 42);
            this.btnAddSprite.Name = "btnAddSprite";
            this.btnAddSprite.Size = new System.Drawing.Size(161, 23);
            this.btnAddSprite.TabIndex = 1;
            this.btnAddSprite.Text = "Add Sprite";
            this.btnAddSprite.UseVisualStyleBackColor = true;
            this.btnAddSprite.Click += new System.EventHandler(this.btnAddSprite_Click);
            // 
            // btnAddContainer
            // 
            this.btnAddContainer.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAddContainer.Location = new System.Drawing.Point(13, 71);
            this.btnAddContainer.Name = "btnAddContainer";
            this.btnAddContainer.Size = new System.Drawing.Size(162, 23);
            this.btnAddContainer.TabIndex = 2;
            this.btnAddContainer.Text = "Add Container";
            this.btnAddContainer.UseVisualStyleBackColor = true;
            this.btnAddContainer.Click += new System.EventHandler(this.btnAddContainer_Click);
            // 
            // AddNewResourceDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(186, 363);
            this.Controls.Add(this.btnAddContainer);
            this.Controls.Add(this.btnAddSprite);
            this.Controls.Add(this.btnAddfile);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "AddNewResourceDialog";
            this.Text = "New Resource";
            this.Load += new System.EventHandler(this.AddNewResourceDialog_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnAddfile;
        private System.Windows.Forms.Button btnAddSprite;
        private System.Windows.Forms.Button btnAddContainer;
    }
}