/*
	srand((unsigned int) time(nullptr));

	int size = 5;
	int * A = new int[size];

	for (int i = 0; i < size; i++)
	{
		A[i] = rand() % 100;
	}

	randomizedQuickSort(A, 0, size - 1);
*/

template <typename T>
int partition(T * A, int p, int r)
{
	T x = A[r];
	int i = (int)p - 1;

	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);

	return i + 1;
}

template <typename T>
void quickSort(T * A, int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);

		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}

int random(int p, int r)
{
	return rand() % (r - p + 1) + (p);
}

template <typename T>
int randomizedPartition(T * A, int p, int r)
{
	swap(A[r], A[random(p, r)]);

	return partition(A, p, r);
}

template <typename T>
void randomizedQuickSort(T * A, int p, int r)
{
	if (p < r) 
	{
		int q = randomizedPartition(A, p, r);

		randomizedQuickSort(A, p, q - 1);
		randomizedQuickSort(A, q + 1, r);
	}
}