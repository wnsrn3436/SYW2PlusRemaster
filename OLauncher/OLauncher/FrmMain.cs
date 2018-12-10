using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace OLauncher
{
    public partial class FrmMain : Form
    {
        string GameDirectory = @"D:\Games\SYW2Plus\";
        string GameName = @"syw2plus.exe";
        string ConfigName = @"config.hq";

        string ProcessesName = @"syw2plus";
        string DllName = @"OLauncherDLL.dll";

        int WaitConfigTime = 1000;

        public FrmMain()
        {
            InitializeComponent();
        }

        void FrmMain_Load(object sender, System.EventArgs e)
        {
            File.Delete(GameDirectory + ConfigName);

            ProcessStartInfo info = new ProcessStartInfo();
            info.WorkingDirectory = GameDirectory;
            info.FileName = GameName;
            using (Process process = Process.Start(info)) { }

            while (!File.Exists(GameDirectory + ConfigName))
                Task.Delay(WaitConfigTime).Wait();

            Injector injector = new Injector(ProcessesName, DllName);
            injector.Inject();
        }
    }
}