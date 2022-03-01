#include <iostream>
#include <vector>

bool CheckAP(std::vector<int> nrs, int AP);

int main() {
    std::vector<int> v1(10);
    int difference;
    bool hasAP;
    std::cout << "Enter 10 values: " << std::endl;
    for (int i = 0; i < v1.capacity(); ++i) {
        std::cin >> v1[i];
    }
    difference = v1[1] - v1[0];
    hasAP = CheckAP(v1, difference);
    std::cout << std::boolalpha << hasAP;
}

bool CheckAP(std::vector<int> nrs, int AP)
{

    for (int i = 2; i < nrs.capacity(); ++i) {
        if (nrs[i] - nrs[i - 1] != AP)
        {
            return false;
        }
    }
    return true;


}
