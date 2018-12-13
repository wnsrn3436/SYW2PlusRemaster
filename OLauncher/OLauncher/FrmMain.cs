using System.IO;
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