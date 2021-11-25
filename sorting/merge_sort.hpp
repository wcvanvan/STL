void merge(int *array, int l, int mid, int r, int *supportArray) {
    int AFlag = l, BFlag = mid + 1;
    for (int i = l; i <= r; i++) {
        if (AFlag > mid) {
            supportArray[i] = array[BFlag];
            BFlag++;
            continue;
        }
        if (BFlag > r) {
            supportArray[i] = array[AFlag];
            AFlag++;
            continue;
        }
        if (array[AFlag] <= array[BFlag]) {
            supportArray[i] = array[AFlag];
            AFlag++;
        } else {
            supportArray[i] = array[BFlag];
            BFlag++;
        }
    }
    for (int i = l; i < r + 1; i++) {
        array[i] = supportArray[i];
    }
}

void merge_sort(int *array, int l, int r, int *supportArray) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(array, l, mid, supportArray);
    merge_sort(array, mid + 1, r, supportArray);
    merge(array, l, mid, r, supportArray);
}