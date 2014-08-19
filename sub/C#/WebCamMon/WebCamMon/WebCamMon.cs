using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WebCamMon
{
    using System;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    /// <summary>
    /// Leon"s webcam mirror
    /// </summary>
    public partial class WebCamMon : Form
    {
        /// <summary>
        /// Webcam handle. 
        /// </summary>
        private int hHwnd;

        public WebCamMon()
        {
            InitializeComponent();
        }

        public struct videohdr_tag
        {
            public byte[] lpData;
            public int dwBufferLength;
            public int dwBytesUsed;
            public int dwTimeCaptured;
            public int dwUser;
            public int dwFlags;
            public int[] dwReserved;
        }

        #region P/Invoke

        [DllImport("avicap32.dll", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        public static extern int capCreateCaptureWindowA([MarshalAs(UnmanagedType.VBByRefStr)]   ref   string lpszWindowName, int dwStyle, int x, int y, int nWidth, short nHeight, int hWndParent, int nID);
        [DllImport("avicap32.dll", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        public static extern bool capGetDriverDescriptionA(short wDriver, [MarshalAs(UnmanagedType.VBByRefStr)]   ref   string lpszName, int cbName, [MarshalAs(UnmanagedType.VBByRefStr)]   ref   string lpszVer, int cbVer);
        [DllImport("user32", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        public static extern bool DestroyWindow(int hndw);
        [DllImport("user32", EntryPoint = "SendMessageA", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        public static extern int SendMessage(int hwnd, int wMsg, int wParam, [MarshalAs(UnmanagedType.AsAny)]   object lParam);
        [DllImport("user32", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        public static extern int SetWindowPos(int hwnd, int hWndInsertAfter, int x, int y, int cx, int cy, int wFlags);
        [DllImport("vfw32.dll")]
        public static extern string capVideoStreamCallback(int hwnd, videohdr_tag videohdr_tag);
        [DllImport("vicap32.dll", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        public static extern bool capSetCallbackOnFrame(int hwnd, string s);

        #endregion

        /// <summary>
        /// Initialize webcam and display the video in a panel.
        /// </summary>
        /// <returns></returns>
        private bool InitializeWebcam()
        {
            bool ok = false;

            int intWidth = this.panel1.Width;
            int intHeight = this.panel1.Height;
            int intDevice = 0;
            string refDevice = intDevice.ToString();

            //Create vedio and get the window handle.
            hHwnd = WebCamMon.capCreateCaptureWindowA(ref refDevice, 1342177280, 0, 0, 1280, 720, this.panel1.Handle.ToInt32(), 0);

            if (WebCamMon.SendMessage(hHwnd, 0x40a, intDevice, 0) > 0)
            {
                WebCamMon.SendMessage(this.hHwnd, 0x435, -1, 0);
                WebCamMon.SendMessage(this.hHwnd, 0x434, 0x42, 0);
                WebCamMon.SendMessage(this.hHwnd, 0x432, -1, 0);
                WebCamMon.SetWindowPos(this.hHwnd, 1, 0, 0, intWidth, intHeight, 6);

                ok = true;
            }
            else
            {
                WebCamMon.DestroyWindow(this.hHwnd);
            }

            return ok;
        }
        /// <summary>
        /// App run, then invoke the webcam till successfully.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WebCamMOn_Load(object sender, EventArgs e)
        {
            bool ok = false;

            while (!ok)
            {
                ok = this.InitializeWebcam();
                System.Threading.Thread.Sleep(100);
            }
        }
        private void CloseWebcam()
        {
            if (this.hHwnd > 0)
            {
                WebCamMon.SendMessage(this.hHwnd, 0x40b, 0, 0);
                WebCamMon.DestroyWindow(this.hHwnd);
            }
        }
        /// <summary>
        /// when close window, destroy the webcam window.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WebCam_FormClosed(object sender, FormClosedEventArgs e)
        {
            CloseWebcam();
        }
        /// <summary>
        /// when window size changed, resize webcam pic.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WebCam_SizeChanged(object sender, EventArgs e)
        {
            WebCamMon.SetWindowPos(this.hHwnd, 1, 0, 0, this.Width, this.Height, 6);
        }
    }
}
