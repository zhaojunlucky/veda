using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utility.Cue
{
    public class CueIndex
    {
        private String indexId;
        private int hour;
        private int minute;
        private int second;

        public String Id
        {
            get;
            set;
        }

        public int Hour
        {
            get;
            set;
        }

        public int Minute
        {
            get;
            set;
        }

        public int Second
        {
            get;
            set;
        }
    }
}
