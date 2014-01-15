using System;
using System.Collections;

namespace LibAutoCSharp
{
	public class IntPairCollection: CollectionBase
	{
		// public methods...
		#region Add
		public int Add(IntPair intPair)
		{
			return List.Add(intPair);
		}
		#endregion
		#region IndexOf
		public int IndexOf(IntPair intPair)
		{
			for(int i = 0; i < List.Count; i++)
				if (this[i] == intPair)    // Found it
					return i;
			return -1;
		}
		#endregion
		#region Insert
		public void Insert(int index, IntPair intPair)
		{
			List.Insert(index, intPair);
		}
		#endregion
		#region Remove
		public void Remove(IntPair intPair)
		{
			List.Remove(intPair);
		}
		#endregion
		#region Find
		// TODO: If desired, change parameters to Find method to search based on a property of IntPair.
		public IntPair Find(IntPair intPair)
		{
			foreach(IntPair intPairItem in this)
				if (intPairItem == intPair)    // Found it
					return intPairItem;
			return null;    // Not found
		}
		#endregion
		#region Contains
		// TODO: If you changed the parameters to Find (above), change them here as well.
		public bool Contains(IntPair intPair)
		{
			return (Find(intPair) != null);
		}
		#endregion
		    	
		// public properties...
		#region this[int index]
		public IntPair this[int index] 
		{
			get
			{
				return (IntPair) List[index];
			}
			set
			{
				List[index] = value;
			}
		}
		#endregion
	}
}
