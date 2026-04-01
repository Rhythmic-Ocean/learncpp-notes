#include <utility>
#include <vector>
double max(double a, double b) { return (a > b) ? a : b; }
void swap(int &a, int &b) { std::swap(a, b); }
int &getLargestElement(std::vector<int> &arr);
