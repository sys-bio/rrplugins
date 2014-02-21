namespace AutoFrontend.Forms
{
    partial class FormChangeBifurcationPlot
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormChangeBifurcationPlot));
            this.panel3 = new System.Windows.Forms.Panel();
            this.chkAntiAlias = new System.Windows.Forms.CheckBox();
            this.panel4 = new System.Windows.Forms.Panel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cmbXAxis = new System.Windows.Forms.ComboBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.cmdOK = new System.Windows.Forms.Button();
            this.cmdCancel = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtMinX = new System.Windows.Forms.TextBox();
            this.txtMaxX = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtMaxY = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtMinY = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.chkLogX = new System.Windows.Forms.CheckBox();
            this.chkLogY = new System.Windows.Forms.CheckBox();
            this.cmdApply = new System.Windows.Forms.Button();
            this.chkXAuto = new System.Windows.Forms.CheckBox();
            this.chkYAuto = new System.Windows.Forms.CheckBox();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.groupBox2);
            this.panel3.Controls.Add(this.chkAntiAlias);
            this.panel3.Controls.Add(this.panel4);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(3, 3);
            this.panel3.Name = "panel3";
            this.panel3.Padding = new System.Windows.Forms.Padding(5);
            this.panel3.Size = new System.Drawing.Size(352, 274);
            this.panel3.TabIndex = 1;
            // 
            // chkAntiAlias
            // 
            this.chkAntiAlias.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.chkAntiAlias.AutoSize = true;
            this.chkAntiAlias.Checked = true;
            this.chkAntiAlias.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkAntiAlias.Location = new System.Drawing.Point(8, 67);
            this.chkAntiAlias.Name = "chkAntiAlias";
            this.chkAntiAlias.Size = new System.Drawing.Size(101, 17);
            this.chkAntiAlias.TabIndex = 1;
            this.chkAntiAlias.Text = "Anti Alias Graph";
            this.chkAntiAlias.UseVisualStyleBackColor = true;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.groupBox1);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(5, 5);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(342, 56);
            this.panel4.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cmbXAxis);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(342, 56);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "X Axis";
            // 
            // cmbXAxis
            // 
            this.cmbXAxis.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cmbXAxis.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbXAxis.Enabled = false;
            this.cmbXAxis.Location = new System.Drawing.Point(3, 16);
            this.cmbXAxis.Name = "cmbXAxis";
            this.cmbXAxis.Size = new System.Drawing.Size(336, 21);
            this.cmbXAxis.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.cmdApply);
            this.panel2.Controls.Add(this.cmdOK);
            this.panel2.Controls.Add(this.cmdCancel);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel2.Location = new System.Drawing.Point(3, 277);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(352, 40);
            this.panel2.TabIndex = 0;
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOK.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdOK.Location = new System.Drawing.Point(106, 8);
            this.cmdOK.Name = "cmdOK";
            this.cmdOK.Size = new System.Drawing.Size(75, 23);
            this.cmdOK.TabIndex = 1;
            this.cmdOK.Text = "OK";
            this.cmdOK.Click += new System.EventHandler(this.cmdOK_Click);
            // 
            // cmdCancel
            // 
            this.cmdCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdCancel.Location = new System.Drawing.Point(187, 8);
            this.cmdCancel.Name = "cmdCancel";
            this.cmdCancel.Size = new System.Drawing.Size(75, 23);
            this.cmdCancel.TabIndex = 0;
            this.cmdCancel.Text = "Cancel";
            this.cmdCancel.Click += new System.EventHandler(this.cmdCancel_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Padding = new System.Windows.Forms.Padding(3);
            this.panel1.Size = new System.Drawing.Size(358, 320);
            this.panel1.TabIndex = 1;
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.chkYAuto);
            this.groupBox2.Controls.Add(this.chkXAuto);
            this.groupBox2.Controls.Add(this.chkLogY);
            this.groupBox2.Controls.Add(this.chkLogX);
            this.groupBox2.Controls.Add(this.txtMaxY);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.txtMinY);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.txtMaxX);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.txtMinX);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(9, 90);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(335, 164);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = " Axis Dimensions";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Min X: ";
            // 
            // txtMinX
            // 
            this.txtMinX.Location = new System.Drawing.Point(53, 17);
            this.txtMinX.Name = "txtMinX";
            this.txtMinX.Size = new System.Drawing.Size(100, 20);
            this.txtMinX.TabIndex = 1;
            this.txtMinX.Text = "0";
            this.txtMinX.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // txtMaxX
            // 
            this.txtMaxX.Location = new System.Drawing.Point(217, 17);
            this.txtMaxX.Name = "txtMaxX";
            this.txtMaxX.Size = new System.Drawing.Size(100, 20);
            this.txtMaxX.TabIndex = 3;
            this.txtMaxX.Text = "0";
            this.txtMaxX.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(171, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Max X: ";
            // 
            // txtMaxY
            // 
            this.txtMaxY.Location = new System.Drawing.Point(217, 43);
            this.txtMaxY.Name = "txtMaxY";
            this.txtMaxY.Size = new System.Drawing.Size(100, 20);
            this.txtMaxY.TabIndex = 7;
            this.txtMaxY.Text = "0";
            this.txtMaxY.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(171, 46);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Max Y: ";
            // 
            // txtMinY
            // 
            this.txtMinY.Location = new System.Drawing.Point(53, 43);
            this.txtMinY.Name = "txtMinY";
            this.txtMinY.Size = new System.Drawing.Size(100, 20);
            this.txtMinY.TabIndex = 5;
            this.txtMinY.Text = "0";
            this.txtMinY.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 46);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(40, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Min Y: ";
            // 
            // chkLogX
            // 
            this.chkLogX.AutoSize = true;
            this.chkLogX.Location = new System.Drawing.Point(10, 78);
            this.chkLogX.Name = "chkLogX";
            this.chkLogX.Size = new System.Drawing.Size(54, 17);
            this.chkLogX.TabIndex = 8;
            this.chkLogX.Text = "Log X";
            this.chkLogX.UseVisualStyleBackColor = true;
            // 
            // chkLogY
            // 
            this.chkLogY.AutoSize = true;
            this.chkLogY.Location = new System.Drawing.Point(10, 101);
            this.chkLogY.Name = "chkLogY";
            this.chkLogY.Size = new System.Drawing.Size(54, 17);
            this.chkLogY.TabIndex = 9;
            this.chkLogY.Text = "Log Y";
            this.chkLogY.UseVisualStyleBackColor = true;
            // 
            // cmdApply
            // 
            this.cmdApply.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdApply.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdApply.Location = new System.Drawing.Point(268, 8);
            this.cmdApply.Name = "cmdApply";
            this.cmdApply.Size = new System.Drawing.Size(75, 23);
            this.cmdApply.TabIndex = 2;
            this.cmdApply.Text = "Apply";
            this.cmdApply.Click += new System.EventHandler(this.cmdApply_Click);
            // 
            // chkXAuto
            // 
            this.chkXAuto.AutoSize = true;
            this.chkXAuto.Location = new System.Drawing.Point(217, 78);
            this.chkXAuto.Name = "chkXAuto";
            this.chkXAuto.Size = new System.Drawing.Size(58, 17);
            this.chkXAuto.TabIndex = 10;
            this.chkXAuto.Text = "Auto X";
            this.chkXAuto.UseVisualStyleBackColor = true;
            // 
            // chkYAuto
            // 
            this.chkYAuto.AutoSize = true;
            this.chkYAuto.Location = new System.Drawing.Point(217, 101);
            this.chkYAuto.Name = "chkYAuto";
            this.chkYAuto.Size = new System.Drawing.Size(61, 17);
            this.chkYAuto.TabIndex = 11;
            this.chkYAuto.Text = "Auto Y ";
            this.chkYAuto.UseVisualStyleBackColor = true;
            // 
            // FormChangeBifurcationPlot
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(358, 320);
            this.Controls.Add(this.panel1);
            try
            {

                this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            }
            catch
            {
            }
            this.Name = "FormChangeBifurcationPlot";
            this.Text = "Change Bifurcation Diagram";
            this.Load += new System.EventHandler(this.FormChangeBifurcationPlot_Load);
            this.VisibleChanged += new System.EventHandler(this.FormChangeBifurcationPlot_VisibleChanged);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormChangeBifurcationPlot_FormClosing);
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.CheckBox chkAntiAlias;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox cmbXAxis;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button cmdOK;
        private System.Windows.Forms.Button cmdCancel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtMaxX;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtMinX;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chkLogY;
        private System.Windows.Forms.CheckBox chkLogX;
        private System.Windows.Forms.TextBox txtMaxY;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtMinY;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button cmdApply;
        private System.Windows.Forms.CheckBox chkXAuto;
        private System.Windows.Forms.CheckBox chkYAuto;
    }
}