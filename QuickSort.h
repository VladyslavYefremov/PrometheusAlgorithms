/*
	srand((unsigned int) time(nullptr));

	size_t size = 5;
	int * A = new int[size];

	for (size_t i = 0; i < size; i++)
	{
		A[i] = rand() % 100;
	}

	randomizedQuickSort(A, 0, size - 1);
*/

template <typename T>
size_t partition(T * A, size_t p, size_t r)
{
	T x = A[r];
	int i = (int)p - 1;

	for (size_t j = p; j < r; j++)
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
void quickSort(T * A, size_t p, size_t r)
{
	if (p < r)
	{
		size_t q = partition(A, p, r);

		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}

int random(size_t p, size_t r)
{
	return rand() % (r - p + 1) + (p);
}

template <typename T>
size_t randomizedPartition(T * A, size_t p, size_t r)
{
	swap(A[r], A[random(p, r)]);

	return partition(A, p, r);
}

template <typename T>
void randomizedQuickSort(T * A, size_t p, size_t r)
{
	if (p < r) 
	{
		size_t q = randomizedPartition(A, p, r);

		randomizedQuickSort(A, p, q - 1);
		randomizedQuickSort(A, q + 1, r);
	}
}