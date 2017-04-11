#include<iostream>
#include<fstream>
#include<string>
#include<time.h>

using namespace std;

bool fileValidity(string filename) {
	ifstream file(filename);
	return file.good();
}

void minHeapify(int numbers[], int index, int high) {
	if (index > high) {
		return;
	}

	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int smallest = index;

	if (left <= high && numbers[left] < numbers[index]) {
		smallest = left;
	}
	
	if (right <= high && numbers[right] < numbers[smallest]) {
		smallest = right;
	}

	if (smallest != index) {
		swap(numbers[index], numbers[smallest]);
		minHeapify(numbers, smallest, high);
	}
}

void buildMinHeap(int numbers[], int count) {
	for (int index = (count-1) / 2 ; index >= 0; index--)
		minHeapify(numbers, index, count);
}

bool isUnique(int numbers[], int n) {
	for (int i = 0; i < 100; i++) {
		if (numbers[i] == n)
			return false;
	}
	return true;
}

int partition(int numbers[], int p, int r)
{
	int x = numbers[r];
	int i = p;

	for (int j = p; j < r; j++) {
		if (numbers[j] <= x) {
			swap(numbers[i++], numbers[j]);
		}
	}

	numbers[r] = numbers[i];
	numbers[i] = x;

	return i;
}

void quicksort(int numbers[], int p, int r)
{
	if (p < r) {
		int q = partition(numbers, p, r);
		quicksort(numbers, p, q - 1);
		quicksort(numbers, q + 1, r);
	}
}

void print(int numbers[], int count) {
	for (int i = count; i > 0; i--) {					
		cout << count - i + 1 << "-) " << numbers[i] << endl;		
	}
}

int main() {
	string fileName;
	int n; int count; int parser = 0;

	cout << "Enter the file name in '.txt' format: ";
	cin >> fileName;

	bool flag = fileValidity(fileName); 

	while (!flag) {
		cout << "File does not exist. Enter a valid file name: ";
		cin >> fileName;
		flag = fileValidity(fileName);
	}

	ifstream file(fileName);

	cout << "Enter the amount of numbers that you want to see (between 1-100): ";
	cin >> count;

	while (true) {
		if (count > 0 && count < 100)
			break;
		else {
			cout << "Enter a valid number: ";
			cin >> count;
		}
	}
	
	int numbers[100];

	clock_t beginning = clock(); 

	while (file >> n) {
		if (parser < count) {
			numbers[parser] = n;
			parser++;
		}
		else {
			buildMinHeap(numbers, count);
			if (numbers[0] < n && isUnique(numbers, n))
				numbers[0] = n;
		}
	}		

	quicksort(numbers, 0, count);	
	
	print(numbers, count);

	clock_t end = clock();

	cout << "This process took " << end - beginning << " clock ticks" << endl;

	return 0;
}
