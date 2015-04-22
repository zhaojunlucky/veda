using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CoreBridge;
using MahApps.Metro.Controls;

namespace ZPlayer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        private UAudioPlayer player = null;
        public MainWindow()
        {
            InitializeComponent();
           // player = new UAudioPlayer();
           // player.OnMute += player_OnMute;
           //// player.open(@"F:\Documents\Musics\Normal\megan nicole - escape.mp3");
           // player.setVolumn(5000);
           // player.setMute(false);
            //player.play();
        }

        void player_OnMute(bool mute)
        {
            
        }
    }
}
