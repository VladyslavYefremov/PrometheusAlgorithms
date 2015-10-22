/*
	T(n) = 3n/2
*/

template <typename T>
void findMinAndMax(T arr[], size_t n, T & min, T & max){

	if (!n)
		return;
	
	if (n > 1) {
		if (n % 2) {
			min = max = arr[0];
		}
		else {
			if (arr[0] > arr[1]) {
				min = arr[1];
				max = arr[0];
			}
			else{
				min = arr[0];
				max = arr[1];
			}
		}

		if (n > 2) {
			for (size_t i = (n % 2) ? 1 : 2; i < n; i += 2) {
				if (arr[i] > arr[i + 1]) {
					if (arr[i] > max)
						max = arr[i];
					if (arr[i + 1] < min)
						min = arr[i + 1];
				}
				else{
					if (arr[i+1] > max)
						max = arr[i];
					if (arr[i] < min)
						min = arr[i + 1];
				}
			}
		}
	}
	else{
		min = max = arr[0];
	}
}