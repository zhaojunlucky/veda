﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utility.Cue
{
    public class CueFile
    {
        private String File
        {
            get;
            set;
        }

        public List<CueTrack> Tracks
        {
            get;
            set;
        }
    }
}
