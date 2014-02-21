using System;

namespace LibAutoCSharp
{
    
	public class DataPoint
	{
	    public int Point { get; set; }

	    public int Type { get; set; }

	    public int Label { get; set; }

	    public double Par { get; set; }


	    public double[] Variables { get; set; }

	    public int NumVariables
		{
			get
			{
				if (Variables == null)
					return 0;
				else return Variables.Length;
			}
		}

		/// <summary>
		/// Initializes a new instance of the DataPoint class.
		/// </summary>
		/// <param name="point"></param>
		/// <param name="type"></param>
		/// <param name="label"></param>
		/// <param name="par"></param>
		/// <param name="var1"></param>
		/// <param name="var2"></param>
		public DataPoint(int point, int type, int label, double par, double[] variables)
		{
			Point = point;
			Type = type;
			Label = label;
			Par = par;
			Variables = variables;
		}



	}
}
