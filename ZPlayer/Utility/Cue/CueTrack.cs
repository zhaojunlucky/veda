using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utility.Cue
{
    public class CueTrack
    {
        private String track = "";
        private String title = "";
        private String performer = "";
        private CueIndex index00 = null;
        private CueIndex index01 = null;
       
        public CueTrack()
        {
        }
        
        public String Track
        {
            set
            {
                track = value;
            }
            get
            {
                return track;
            }
        }

        public String Title
        {
            set
            {
                title = value;
            }
            get
            {
                return title;
            }
        }
        public String Performer
        {
            set
            {
                performer = value;
            }
            get
            {
                return performer;
            }
        }
        public CueIndex Index00
        {
            set
            {
                index00 = value;
            }
            get
            {
                return index00;
            }
        }
        public CueIndex Index01
        {
            set
            {
                index01 = value;
            }
            get
            {
                return index01;
            }
        }
    }
}
