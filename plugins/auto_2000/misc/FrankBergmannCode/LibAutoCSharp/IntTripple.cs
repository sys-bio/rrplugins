using System;
using System.Collections;

namespace LibAutoCSharp
{
    public class IntTripple
    {
        private int _Key;
        public int Key
        {
            get { return _Key; }
            set { _Key = value; }
        }

        private int _Value1;
        public int Value1
        {
            get { return _Value1; }
            set { _Value1 = value; }
        }

        private int _Value2;
        public int Value2
        {
            get { return _Value2; }
            set { _Value2 = value; }
        }

        /// <summary>
        /// Initializes a new instance of the IntTripple class.
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value1"></param>
        /// <param name="value2"></param>
        public IntTripple(int key, int value1, int value2)
        {
            _Key = key;
            _Value1 = value1;
            _Value2 = value2;
        }

        public IntTripple()
        {

        }

        public override string ToString()
        {
            return String.Format("{0} {1}: {2}", UtilLib.ConvertIntTypeToShortString(_Value2), UtilLib.ConvertIntTypeToString(_Value2), _Value1);
        }
    }
}
