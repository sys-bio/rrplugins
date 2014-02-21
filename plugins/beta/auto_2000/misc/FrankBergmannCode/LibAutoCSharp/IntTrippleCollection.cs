using System;
using System.Collections;

namespace LibAutoCSharp
{
    public class IntTrippleCollection : CollectionBase
    {
        // public methods...
        #region Add
        public int Add(IntTripple intTripple)
        {
            return List.Add(intTripple);
        }
        #endregion
        #region IndexOf
        public int IndexOf(IntTripple intTripple)
        {
            for (int i = 0; i < List.Count; i++)
                if (this[i] == intTripple)    // Found it
                    return i;
            return -1;
        }
        #endregion
        #region Insert
        public void Insert(int index, IntTripple intTripple)
        {
            List.Insert(index, intTripple);
        }
        #endregion
        #region Remove
        public void Remove(IntTripple intTripple)
        {
            List.Remove(intTripple);
        }
        #endregion
        #region Find
        // TODO: If desired, change parameters to Find method to search based on a property of IntTripple.
        public IntTripple Find(IntTripple intTripple)
        {
            foreach (IntTripple intTrippleItem in this)
                if (intTrippleItem == intTripple)    // Found it
                    return intTrippleItem;
            return null;    // Not found
        }
        #endregion
        #region Contains
        // TODO: If you changed the parameters to Find (above), change them here as well.
        public bool Contains(IntTripple intTripple)
        {
            return (Find(intTripple) != null);
        }
        #endregion

        // public properties...
        #region this[int index]
        public IntTripple this[int index]
        {
            get
            {
                return (IntTripple)List[index];
            }
            set
            {
                List[index] = value;
            }
        }
        #endregion
    }
}
