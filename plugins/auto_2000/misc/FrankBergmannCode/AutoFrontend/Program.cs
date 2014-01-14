using System;
using System.Globalization;
using System.Threading;
using System.Windows.Forms;
using SBW;

namespace AutoFrontend
{
    /// <summary>
    ///     Summary description for Program.
    /// </summary>
    public class Program
    {
        /// <summary>
        ///     The main entry point for the application.
        /// </summary>
        [STAThread]
        private static void Main(string[] args)
        {
            CultureInfo culture = CultureInfo.CreateSpecificCulture("en");
            culture.NumberFormat.NumberDecimalSeparator = ".";
            Thread.CurrentThread.CurrentCulture = culture;

            //Application.SetCompatibleTextRenderingDefault(false); 
            Application.EnableVisualStyles();
            Application.DoEvents();


            MainForm newForm1 = MainForm.Instance;
            object oBox = newForm1;

            var oImpl = new ModuleImplementation(
                "AutoCSharp", "Auto CSharp", LowLevel.ModuleManagementType.UniqueModule,
                "Direct Interface to AUTO2000 with C# frontend");
            oImpl.addService("auto", "Auto2000 (C#)", "/Analysis", "Direct Interface to AUTO2000 with C# frontend",
                             ref oBox);
            oImpl.EnableServices(args);
            MainForm.IsSBWAvailable = true;
            Application.Run(newForm1);
        }
    }
}