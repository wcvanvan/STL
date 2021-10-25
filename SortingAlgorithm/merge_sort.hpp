void Merge(int* array, int l, int mid, int r, int* sortedArray) {
	int AFlag = l, BFlag = mid + 1;
	int length = r - l + 1;
	for (int i = l; i <= r; i++)
	{
		if (AFlag > mid) {
			sortedArray[i] = array[BFlag];
			BFlag++;
			continue;
		}
		if (BFlag > r)
		{
			sortedArray[i] = array[AFlag];
			AFlag++;
			continue;
		}
		if (array[AFlag] <= array[BFlag])
		{
			sortedArray[i] = array[AFlag];
			AFlag++;
		}
		else {
			sortedArray[i] = array[BFlag];
			BFlag++;
		}
	}
	for (int i = l; i < r+1; i++)
	{
		array[i] = sortedArray[i];
	}
}

void MergeSort(int* array, int l, int r, int* sortedArray) {
	if (l >= r) {
		return;
	}
	int mid = (l + r) / 2;
	MergeSort(array, l, mid, sortedArray);
	MergeSort(array, mid + 1, r, sortedArray);
	Merge(array, l, mid, r, sortedArray);
}