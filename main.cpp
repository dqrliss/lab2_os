#include <iostream>
#include <windows.h>

int n, avg = 0, max = INT_MIN, min = INT_MAX, ind_max = 0, ind_min = 0;
int* arr;

DWORD WINAPI min_max() {
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            ind_max = i;
        }
        Sleep(7);
        if (arr[i] < min) {
            min = arr[i];
            ind_min = i;
        }
        Sleep(7);
    }
    std::cout << "max value: " << max << "\nmin value: " << min;
    return 0;
}

DWORD WINAPI average() {
    for (int i = 0; i < n; i++) {
        avg += arr[i];
        Sleep(12);
    }
    avg /= n;
    std::cout << "\naverage value: " << avg << "\n";
    return 0;
}


int main() {

    std::cout << "array size: ";
    std::cin >> n;
    arr = new int[n];
    std::cout << "array elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    HANDLE hThread_;
    DWORD IDThread_;
    HANDLE hThread;
    DWORD IDThread;
    hThread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)min_max, NULL, 0, &IDThread_);
    if (hThread_ == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(hThread_, INFINITE);
    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)average, NULL, 0, &IDThread);
    if (hThread == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hThread_);

    arr[ind_max] = avg;
    arr[ind_min] = avg;
    std::cout << ind_max << " array element(max): " << arr[ind_max] << "\n" << ind_min << " array element(min): " << arr[ind_min];
    delete[] arr;
    return 0;
}
