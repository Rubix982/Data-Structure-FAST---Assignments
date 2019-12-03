#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int n, k;

typedef unsigned long long ull;

ull func(int i, int arr[], int start, int end) {

    ull max = -9999, min = 9999;
    for ( int j = start ; j < end ; ++i ) if ( max < arr[j] ) max = arr[j];

    for (int j = start; j < end; ++i) if (min > arr[j]) min = arr[j];

    return max - min;
}

int main(void) {

    std::cin >> n >> k;

    int array[n];
    std::vector<int> values(k);
    std::vector<ull> costs;

    for ( int i = 0 ; i < n ; ++i ) std::cin >> array[i];

    if ( k == 1 ) {
        std::cout << array[n - 1] - array[0] << "\n";
        return 0;
    } else if ( k <= n ) {
        std::cout << "0" << "\n";
        return 0;
    } else if ( k > n) {
        int start = 0;

        for ( int i = 0 ; i < k && start < n ; ++i ) {
            ull temp = func(i, array, start, start + 1);
            costs.push_back(temp);
            start++;
        }
    }

    std::sort(costs.begin(), costs.end());
    for ( const auto & x : costs )
        std::cout << x << " ";
    std::cout << costs.size() << "\n";

    return 0;
}