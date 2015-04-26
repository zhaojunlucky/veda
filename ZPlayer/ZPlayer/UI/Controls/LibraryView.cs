using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace ZPlayer.UI.Controls
{
    public class LibraryView : ViewBase
    {
        #region DefaultStyleKey

        protected override object DefaultStyleKey
        {
            get { return new ComponentResourceKey(GetType(), "LibraryView"); }
        }

        #endregion

        #region ItemContainerDefaultStyleKey

        protected override object ItemContainerDefaultStyleKey
        {
            get { return new ComponentResourceKey(GetType(), "LibraryViewItem"); }
        }

        #endregion
    }

    /// <summary>
    /// FileCollection is used as ItemsSource of ListView. ListView will show files inside
    /// the collection
    /// </summary>
    public sealed class FileCollection : ObservableCollection<FileSystemInfo>
    {
        public FileCollection()
        {
            // put files in %windir%\web\wallpaper into the collection

            // get %windir%
            string windir = Environment.GetEnvironmentVariable("WINDIR");
            if (string.IsNullOrEmpty(windir))
                return;

            // put files into collection
            string wallpaperPath = string.Format(@"{0}\Web\Wallpaper\Theme2", windir);
            DirectoryInfo info = new DirectoryInfo(wallpaperPath);
            FileSystemInfo[] files = info.GetFileSystemInfos();
            foreach (FileSystemInfo fi in files)
            {
                // exlude hidden files 
                if ((fi.Attributes & FileAttributes.Hidden) != FileAttributes.Hidden)
                    Add(fi);
            }
        }
    }
}
