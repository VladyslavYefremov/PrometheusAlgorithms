using System;

namespace AlgorithmsLibrary
{
    public static class Counting
    {
        /// <summary>
        /// Standart method of Counting sort
        /// </summary>
        /// <param name="A">An array that needs to be sorted</param>
        /// <param name="B">Sorted array</param>
        /// <param name="k">The biggest element of array A</param>
        public static void Sort(int[] A, int[] B, uint k)
        {
            uint[] C = new uint[k + 1];

            int L = A.Length;

            for (uint i = 0; i < (k + 1); i++)
                C[i] = 0;
            
            for (uint i = 0; i < L; i++)
                C[A[i]]++;
            
            for (uint i = 1; i < (k + 1); i++)
                C[i] += C[i - 1];
            
            for (int i = (L - 1); i >= 0; i--)
            {
                B[C[A[i]] - 1] = A[i];
                C[A[i]]--;
            }
        }
        /// <summary>
        /// Additional method for Radix sort
        /// </summary>
        /// <param name="A">An array that needs to be sorted</param>
        /// <param name="B">Result: Sorted array A</param>
        /// <param name="k">The biggest value of radix (default: 9)</param>
        /// <param name="d">The number of radix</param>
        public static void Sort(int[] A, int[] B, uint k, uint d)
        {
            int L = A.Length;
            uint[] C = new uint[k + 1];

            for (int i = 0; i < (k + 1); i++)
                C[i] = 0;

            for (int i = 0; i < L; i++)
                C[getRadix(A[i], d)]++;

            for (int i = 1; i < (k + 1); i++)
                C[i] += C[i - 1];

            for (int i = (L - 1); i >= 0; i--)
            {
                B[C[getRadix(A[i], d)] - 1] = A[i];
                C[getRadix(A[i], d)]--;
            }

            for (int i = 0; i < A.Length; i++)
                A[i] = B[i];
        }
        /// <summary>
        /// Gets the radix number 'd' from 'value'
        /// </summary>
        /// <param name="value"></param>
        /// <param name="d"></param>
        /// <returns>The radix number "d" from value</returns>
        private static int getRadix(int value, uint d)
        {
            int result = 0;
            for (uint i = 0; i < d; i++)
            {
                result = value % 10;
                value /= 10;
            }
            return result;
        }
    }
}
