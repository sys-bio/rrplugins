namespace AutoFrontend
{
    public class NameValuePair
    {
        /// <summary>
        ///     Initializes a new instance of the NameValuePair class.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public NameValuePair(string name, object value)
        {
            Name = name;
            Value = value;
        }

        public string Name { get; set; }

        public object Value { get; set; }
    }
}