using System;

/*
    Worst case performance	O(wn)
    Worst case space complexity	O(w + N)
*/

namespace AlgorithmsLibrary
{
    public static class Radix
    {
        public static void Sort(int[] A, uint d)
        {
            int[] B = new int[A.Length];

            for (uint i = 0; i < d; i++)
            {
                Counting.Sort(A, B, 9, i + 1);
            }
        }
    }
}
