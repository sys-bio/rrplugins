using System;
using System.Collections;
using System.Collections.Specialized;
using System.IO;

namespace LibAutoCSharp
{
    public class AutoResultRunCollection : CollectionBase
    {
        // public methods...
        #region Add
        public int Add(AutoResultRun autoResultRun)
        {
            return List.Add(autoResultRun);
        }
        #endregion
        #region IndexOf
        public int IndexOf(AutoResultRun autoResultRun)
        {
            for (int i = 0; i < List.Count; i++)
                if (this[i] == autoResultRun)    // Found it
                    return i;
            return -1;
        }
        #endregion
        #region Insert
        public void Insert(int index, AutoResultRun autoResultRun)
        {
            List.Insert(index, autoResultRun);
        }
        #endregion
        #region Remove
        public void Remove(AutoResultRun autoResultRun)
        {
            List.Remove(autoResultRun);
        }
        #endregion
        #region Find
        // TODO: If desired, change parameters to Find method to search based on a property of AutoResultRun.
        public AutoResultRun Find(AutoResultRun autoResultRun)
        {
            foreach (AutoResultRun autoResultRunItem in this)
                if (autoResultRunItem == autoResultRun)    // Found it
                    return autoResultRunItem;
            return null;    // Not found
        }
        #endregion
        #region Contains
        // TODO: If you changed the parameters to Find (above), change them here as well.
        public bool Contains(AutoResultRun autoResultRun)
        {
            return (Find(autoResultRun) != null);
        }
        #endregion

        // public properties...
        #region this[int index]
        public AutoResultRun this[int index]
        {
            get
            {
                return (AutoResultRun)List[index];
            }
            set
            {
                List[index] = value;
            }
        }
        #endregion
    }
}
