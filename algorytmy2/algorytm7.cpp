#include <iostream>
#include <ctime>
#include <time.h>


using namespace std;

int N = 12345678;
/*
double d(double x, double y) {
    if ((x - 5) * (x - 5) + (y - 5) * (y - 5) < 10) {
        return 100;
    }
        return 0;
}
*/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int x{};
    int y{};
    cin >> x >> y;
    double x2, y2, distance{}, result{};
    int circleP{};
    srand(time(NULL));//ustawienie liczb pseudolosowych zależnych od czasu

    while(--N)
    {
        x2 = (float)(rand()) / (float)(RAND_MAX / x);//RAND max 32767
        y2 = (float)(rand()) / (float)(RAND_MAX / y); 

        distance = d(x2, y2);
        if (0 < distance) {
            result += distance;

        }
        ++circleP;
    }
    cout << (int)((result / circleP) * x * y);

}