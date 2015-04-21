using log4net;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utility.Cue
{
    public class Cue
    {
        private String performer = "";
        private String title = "";

        private List<CueFile> cueFiles = new List<CueFile>();
        private ILog logger = LogManager.GetLogger(typeof(Cue));

        public Cue(String cueFile, Boolean validateFileExists)
        {
            parse(cueFile, validateFileExists);
        }

        public Cue(String cueFile)
            : this(cueFile,false)
        {
          
        }

        private void clear()
        {
            cueFiles.Clear();
            performer = "";
            title = "";
        }
        public void parse(string cueFile, bool validateFileExists)
        {
            clear();
            if(!cueFile.EndsWith(".cue",StringComparison.OrdinalIgnoreCase))
            {
                throw new Exception("File extension is not cue.");
            }
            if(!File.Exists(cueFile))
            {
                throw new Exception("Cue file doesn't exist.");
            }
            StreamReader sr = null;
            try
            {
                sr = new StreamReader(cueFile);
                parse(sr);
            }
            finally
            {
                if(sr != null)
                {
                    sr.Close();
                }
            }
        }

        private void parse(StreamReader sr)
        {
            string line = null;
            while((line = sr.ReadLine()) != null)
            {

            }
        }

        public String Performer
        {
            get;
            set;
        }

        public String Title
        {
            get;
            set;
        }

        public List<CueFile> CueFiles
        {
            get;
            set;
        }
    }
}
