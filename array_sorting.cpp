#include <iostream>
using namespace std;

const int SIZE = 8;

void oddsKeepEvensFlip(int arr[], int arrSize);
void printArray(int arr[],int arrSize);

int main(){

    int arr[SIZE] = {5, 2, 11, 7, 6, 4,8,13};
    cout<< "Input array: "<<endl;
    printArray(arr,SIZE);

    cout<<endl<<endl<<"After calling oddsKeepEvensFlip(): "<<endl;
    oddsKeepEvensFlip(arr, SIZE);
    printArray(arr,SIZE);
    cout<<endl<<endl;

    return 0;

}

void oddsKeepEvensFlip(int arr[], int arrSize){
    int outputArr[arrSize];
    int oddCount = 0;
    int evenCount = arrSize - 1;

    for (int i = 0; i < arrSize; i++){
        if (arr[i] % 2 != 0){
            outputArr[oddCount] = arr[i];
            oddCount++;
        }
        else{
            outputArr[evenCount] = arr[i];
            evenCount--;
        }
    }
    for (int j = 0; j < arrSize; j++){
        arr[j] = outputArr[j];
    }

}

void printArray(int arr[],int arrSize){
    for (int i=0;i<arrSize;i++)
        cout<<arr[i]<<" ";
}
