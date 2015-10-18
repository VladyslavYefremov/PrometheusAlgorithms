#include <limits>

void Merge(int * A, unsigned int p, unsigned int q, unsigned int r){
	unsigned int s1 = q - p + 1;
	unsigned int s2 = r - q;

	int * L = new int[s1];
	int * R = new int[s2];

	for (unsigned int i = 0; i < s1; i++) {
		L[i] = A[p + i];
	}

	for (unsigned int i = 0; i < s2; i++) {
		R[i] = A[q + i + 1];
	}

	L[s1] = std::numeric_limits<int>::max();
	R[s2] = std::numeric_limits<int>::max();

	unsigned int i = 0;
	unsigned int j = 0;

	for (unsigned int k = p; k < r + 1; k++) {
		if (L[i] <= R[j]){
			A[k] = L[i];
			i++;
		}
		else{
			A[k] = R[j];
			j++;
		}
	}

	delete[] L;
	delete[] R;
}

void MergeSort(int * A, unsigned int p, unsigned int r){
	if (p >= r)
		return;

	unsigned int q = (p + r) / 2;

	MergeSort(A, p, q);
	MergeSort(A, q + 1, r);
	Merge(A, p, q, r);
}

/*
	int * array = new int[n];
	...
	MergeSort(array, 0, n-1);
	delete[] array;
*/
