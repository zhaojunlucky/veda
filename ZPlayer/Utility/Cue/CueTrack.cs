using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utility.Cue
{
    public class CueTrack
    {  
        public CueTrack()
        {
        }
        
        public String Track
        {
            get;
            set;
        }

        public String Title
        {
            get;
            set;
        }
        public String Performer
        {
            get;
            set;
        }
        public CueIndex Index00
        {
            get;
            set;
        }
        public CueIndex Index01
        {
            get;
            set;
        }
    }
}
