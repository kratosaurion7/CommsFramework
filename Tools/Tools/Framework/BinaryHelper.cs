using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tools.Framework
{
    public class BinaryHelper
    {
        public static byte[] GetBytes(string contents, Encoding enc)
        {
            byte[] results;

            if (!BitConverter.IsLittleEndian)
            {
                results = enc.GetBytes(contents);
            }
            else
            {
                results = enc.GetBytes(contents).Reverse().ToArray();
            }

            return results;
        }

        public static byte[] GetBytes(int contents)
        {
            byte[] results;

            //if (!BitConverter.IsLittleEndian)
            //{
            results = BitConverter.GetBytes(contents);
            //}
            //else
            //{
            //    results = BitConverter.GetBytes(contents).Reverse().ToArray();
            //}

            return results;
        }
    }
}
