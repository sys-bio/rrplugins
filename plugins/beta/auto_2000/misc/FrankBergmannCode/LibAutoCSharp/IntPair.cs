using System;
using System.Collections;

namespace LibAutoCSharp
{

	/// <summary>
	/// Summary description for IntPair.
	/// </summary>
	public class IntPair
	{
		private int _Key;
		public int Key
		{
			get {	return _Key; }
			set { _Key = value;	}
		}

		private int _Value;
		public int Value
		{
			get {	return _Value; }
			set { _Value = value;	}
		}
		/// <summary>
		/// Initializes a new instance of the IntPair class.
		/// </summary>
		/// <param name="nKey"></param>
		/// <param name="nValue"></param>
		public IntPair(int nKey, int nValue)
		{
			_Key = nKey;
			_Value = nValue;
		}
		public IntPair()
		{
			//
			// TODO: Add constructor logic here
			//
		}
	}
    
}
