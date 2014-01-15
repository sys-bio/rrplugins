using System;
using System.Collections;

namespace LibAutoCSharp
{
    public class IntDoublePairCollection : CollectionBase
    {
        // public methods...
        #region Add
        public int Add(IntDoublePair intDoublePair)
        {
            return List.Add(intDoublePair);
        }
        #endregion
        #region IndexOf
        public int IndexOf(IntDoublePair intDoublePair)
        {
            for (int i = 0; i < List.Count; i++)
                if (this[i] == intDoublePair)    // Found it
                    return i;
            return -1;
        }
        #endregion
        #region Insert
        public void Insert(int index, IntDoublePair intDoublePair)
        {
            List.Insert(index, intDoublePair);
        }
        #endregion
        #region Remove
        public void Remove(IntDoublePair intDoublePair)
        {
            List.Remove(intDoublePair);
        }
        #endregion
        #region Find
        // TODO: If desired, change parameters to Find method to search based on a property of IntDoublePair.
        public IntDoublePair Find(IntDoublePair intDoublePair)
        {
            foreach (IntDoublePair intDoublePairItem in this)
                if (intDoublePairItem == intDoublePair)    // Found it
                    return intDoublePairItem;
            return null;    // Not found
        }
        #endregion
        #region Contains
        // TODO: If you changed the parameters to Find (above), change them here as well.
        public bool Contains(IntDoublePair intDoublePair)
        {
            return (Find(intDoublePair) != null);
        }
        #endregion

        // public properties...
        #region this[int index]
        public IntDoublePair this[int index]
        {
            get
            {
                return (IntDoublePair)List[index];
            }
            set
            {
                List[index] = value;
            }
        }
        #endregion
    }
}
