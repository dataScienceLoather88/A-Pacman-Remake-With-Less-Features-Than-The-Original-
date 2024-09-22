#pragma once
#include<iostream>
const int resolutionX = 252;
const int resolutionY = 324;
const int boxPixelsX = 9;
const int boxPixelsY = 9;
const int gameRows = resolutionY / boxPixelsY; // Total rows on grid
const int gameColumns = resolutionX / boxPixelsX; // Total columns on grid
const int largeSpriteDimensionX = 15;
const int largeSpriteDimensionY = 15;

using namespace std;

void bubbleSort(int arr[], int arr2[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++) {
		swapped = false;
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				swap(arr2[j], arr2[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}