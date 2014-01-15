using System;
using System.Collections;

namespace LibAutoCSharp
{
    public class IntDoublePair
    {
        private int _Key;
        public int Key
        {
            get
            {
                return _Key;
            }
            set
            {
                _Key = value;
            }
        }
        private double _Value;
        public double Value
        {
            get
            {
                return _Value;
            }
            set
            {
                _Value = value;
            }
        }

        public IntDoublePair()
        {

        }

        /// <summary>
        /// Initializes a new instance of the IntDoublePair class.
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        public IntDoublePair(int key, double value)
        {
            _Key = key;
            _Value = value;
        }
    }
    
}
