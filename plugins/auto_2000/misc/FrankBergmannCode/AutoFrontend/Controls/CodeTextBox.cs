using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace AutoFrontend.Controls
{
    /// <summary>
    ///     Summary description for CodeTextBox.
    /// </summary>
    public class CodeTextBox : TextBox
    {
        /// <summary>
        ///     Required designer variable.
        /// </summary>
        private Container components;

        public CodeTextBox()
        {
            // This call is required by the Windows.Forms Form Designer.
            InitializeComponent();

            Multiline = true;
            Font = new Font("Courier New", 11);
            MaxLength = 0;
            ScrollBars = ScrollBars.Both;
            WordWrap = false;
        }

        /// <summary>
        ///     Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null)
                    components.Dispose();
            }
            base.Dispose(disposing);
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: Add custom paint code here

            // Calling the base class OnPaint
            base.OnPaint(pe);
        }

        #region Component Designer generated code

        /// <summary>
        ///     Required method for Designer support - do not modify
        ///     the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
        }

        #endregion
    }
}