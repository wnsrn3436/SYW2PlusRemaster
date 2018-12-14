using System.IO;
using System.Xml;
using System.Diagnostics;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace OLauncher
{
    public partial class FrmMain : Form
    {
        string GameDirectory = @"D:\Games\SYW2Plus\";
        string GameFileName = @"syw2plus.exe";

        string ConfigFileName = @"config.hq";
        int WaitConfigInterval = 1000;

        string GameProcessName = @"syw2plus";
        string LauncherDllName = @"OLauncherDLL.dll";

        public FrmMain()
        {
            InitializeComponent();
        }

        void BtnStart_Click(object sender, System.EventArgs e)
        {
            XmlDocument document = new XmlDocument();
            document.Load("Configs.xml");

            var elements = document.SelectNodes("/Configs/Category");
            foreach (XmlNode element in elements) element.Attributes["used"].Value = "0";
            foreach (XmlNode element in elements) if (element.Attributes["name"].Value == "Normal") element.Attributes["used"].Value = "1";

            document.Save("Configs.xml");

            GameStart();
        }

        void BtnStart2_Click(object sender, System.EventArgs e)
        {
            XmlDocument document = new XmlDocument();
            document.Load("Configs.xml");

            var elements = document.SelectNodes("/Configs/Category");
            foreach (XmlNode element in elements) element.Attributes["used"].Value = "0";
            foreach (XmlNode element in elements) if (element.Attributes["name"].Value == "Scenario") element.Attributes["used"].Value = "1";

            document.Save("Configs.xml");

            GameStart();
        }

        void BtnStart3_Click(object sender, System.EventArgs e)
        {
            XmlDocument document = new XmlDocument();
            document.Load("Configs.xml");

            var elements = document.SelectNodes("/Configs/Category");
            foreach (XmlNode element in elements) element.Attributes["used"].Value = "0";
            foreach (XmlNode element in elements) if (element.Attributes["name"].Value == "MapEditor") element.Attributes["used"].Value = "1";

            document.Save("Configs.xml");

            GameStart();
        }

        void GameStart()
        {
            if (Process.GetProcessesByName(GameProcessName).Length == 0)
            {
                ProcessStartInfo info = new ProcessStartInfo()
                {
                    WorkingDirectory = GameDirectory,
                    FileName = GameFileName
                };
                using (Process process = Process.Start(info)) { }

                File.Delete(GameDirectory + ConfigFileName);
                Task.Run(
                    () =>
                    {
                        while (!File.Exists(GameDirectory + ConfigFileName))
                            Task.Delay(WaitConfigInterval).Wait();

                        Injector injector = new Injector(GameProcessName, LauncherDllName);
                        injector.Inject();
                    }
                );
            }
        }
    }
}