using System;
using System.Collections;

namespace LibAutoCSharp
{
    public class IntCollection : CollectionBase
    {
        // public methods...
        #region Add
        public int Add(int @int)
        {
            return List.Add(@int);
        }
        #endregion
        #region IndexOf
        public int IndexOf(int @int)
        {
            for (int i = 0; i < List.Count; i++)
                if (this[i] == @int)    // Found it
                    return i;
            return -1;
        }
        #endregion
        #region Insert
        public void Insert(int index, int @int)
        {
            List.Insert(index, @int);
        }
        #endregion
        #region Remove
        public void Remove(int @int)
        {
            List.Remove(@int);
        }
        #endregion
        #region Find
        // TODO: If desired, change parameters to Find method to search based on a property of Int.
        public int Find(int @int)
        {
            foreach (int @intItem in this)
                if (@intItem == @int)    // Found it
                    return @intItem;
            return int.MinValue;    // Not found
        }
        #endregion
        #region Contains
        // TODO: If you changed the parameters to Find (above), change them here as well.
        public bool Contains(int @int)
        {
            return (Find(@int) != int.MinValue);
        }
        #endregion

        // public properties...
        #region this[int index]
        public int this[int index]
        {
            get
            {
                return (int)List[index];
            }
            set
            {
                List[index] = value;
            }
        }
        #endregion
    }
}
