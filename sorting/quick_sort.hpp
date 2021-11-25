#include <ctime>
#include <cstdlib>
#include <random>

std::random_device rd;
std::minstd_rand engine(rd());

void quicksort(int* array, int* supportArray, int L, int R) {
	if (L >= R)
	{
		return;
	}
    std::uniform_int_distribution<int> distribution(L, R);
	int pivot = distribution(engine);
	int l = L, r = R;
	for (int i = L; i <= R; i++)
	{
		if (i == pivot)
		{
			continue;
		}
		if (array[i] <= array[pivot])
		{
			supportArray[l++] = array[i];
		}
		else {
			supportArray[r--] = array[i];
		}
	}
	supportArray[l] = array[pivot];
	for (int i = L; i <= R; i++)
	{
		array[i] = supportArray[i];
	}
	quicksort(array, supportArray, L, l - 1);
	quicksort(array, supportArray, l + 1, R);
}