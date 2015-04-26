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
        private LinkedList<Navigation> childs = new LinkedList<Navigation>();
        public delegate void NavigateHandler(Navigation nv);
        public event NavigateHandler NavigateEvent = null;
        public NavigationBar()
        {
            InitializeComponent();
            addNavigationUI(root,false);
            childs.AddLast(root);
            //addNavigation(new Navigation { Name = "周杰伦", Action = "周杰伦" });
            //addNavigation(new Navigation { Name = "七里香", Action = "七里香" });
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
            addNavigationUI(navigation, true);
            childs.AddLast(navigation);
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
            tb.FontSize = 18;
            tb.Tag = navigation;
            
            navigation.Tag = tb;
            panel.Children.Add(tb);
            this.container.Children.Add(panel);
            if(childs.Last != null)
            {
                var tbl = (TextBlock)(childs.Last.Value.Tag);
                tbl.Cursor = Cursors.Hand;
                tbl.Foreground = Brushes.Green;
                tbl.MouseDown += tb_MouseDown;
            }
        }

        void tb_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if(sender is TextBlock)
            {
                var tb = sender as TextBlock;
                if(tb != null)
                {
                    tb.Cursor = Cursors.Arrow;
                    tb.MouseDown -= tb_MouseDown;
                    

                    var nv = tb.Tag as Navigation;
                    var node = childs.Find(nv);
                    // click home
                    var removeNode = node.Next;
                    tb.Foreground = ((removeNode.Value as Navigation).Tag as TextBlock).Foreground ;
                    int count = 0;
                    while (removeNode != null)
                    {
                        ++count;
                        var n = removeNode.Next;
                        childs.Remove(removeNode);
                        removeNode = n;
                    }
                    count *= 2;
                    this.container.Children.RemoveRange(this.container.Children.Count - count, count);
                    if(NavigateEvent != null)
                    {
                        nv.Tag = null;
                        NavigateEvent(nv);
                    }
                }
            }
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
