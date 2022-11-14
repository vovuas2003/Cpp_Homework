#include <vector>
#include <iostream>
#include <algorithm>

using std::cout, std::endl, std::vector, std::cin;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<int>::iterator ma = std::max_element(v.begin(), v.end());
    std::sort(v.begin(), ma);
    std::sort(ma, v.end()); 
    std::reverse(ma, v.end());
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}
