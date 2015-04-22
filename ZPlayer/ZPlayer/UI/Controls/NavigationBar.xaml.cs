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

namespace ZPlayer.UI.Controls
{
    /// <summary>
    /// Interaction logic for NavigationBar.xaml
    /// </summary>
    public partial class NavigationBar : UserControl
    {
        private Navigation root = new Navigation { Name = "Home", Action = "home" };
        LinkedList<Navigation> childs = new LinkedList<Navigation>();
        public NavigationBar()
        {
            InitializeComponent();
            addNavigationUI(root,false);
            addNavigationUI(new Navigation { Name = "周杰伦", Action = "周杰伦" }, true);
        }

        public Navigation Root
        {
            get
            {
                return root;
            }
        }

        public void addNavigation(Navigation navigation)
        {
            childs.AddLast(navigation);
            addNavigationUI(navigation, true);
            
        }

        private void addNavigationUI(Navigation navigation, bool addSeparatorBefore)
        {
            if (addSeparatorBefore)
            {
                addSeparatorArrow();
            }
            StackPanel panel = new StackPanel();
            panel.Orientation = Orientation.Horizontal;
            TextBlock tb = new TextBlock();
            tb.Text = navigation.Name;
            tb.FontSize = 14;
            tb.Tag = navigation;
            tb.Cursor = Cursors.Hand;
            tb.Foreground = Brushes.Green;

            panel.Children.Add(tb);
            this.container.Children.Add(panel);
        }

        private void addSeparatorArrow()
        {
            StackPanel panel = new StackPanel();
            panel.Orientation = Orientation.Horizontal;
            TextBlock arrow = new TextBlock();
            arrow.Text = " > ";
            arrow.FontSize = 14;
            panel.Children.Add(arrow);
            this.container.Children.Add(panel);
        }
    }
}
