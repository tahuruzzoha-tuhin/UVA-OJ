#include <iostream>
#include <vector>
#include <complex>
#include <sstream>

// General idea is:
    // The max # contained will always be able to be formed with 2 on the perimiter

using namespace std;


// Lots of code from the code archive, points of intersection of two circles
typedef complex<double> Point;
const double eps = 1e-6;

const double Radius = 2.5;


struct Circle
{
    Point c;
    double r;

    Circle(Point c, double r)
        : c(c), r(r)
    {}
};

int N;
Point allPoints[205];

// Determines the inersection point beween the two, if there is one
void line_circ_inter(const Circle &a, const Circle &b, vector<Point> & inter)
{
    double d2 = norm(b.c-a.c), rS = a.r + b.r, rD = a.r - b.r;
    if (d2 > rS * rS || d2 < rD*rD) return;

    double ca = 0.5*(1 + rS * rD / d2);
    Point z = Point(ca, sqrt((a.r*a.r/d2)-ca*ca));
    inter.push_back(a.c + (b.c-a.c)*z);
    if (fabs(z.imag())>eps)
        inter.push_back(a.c + (b.c-a.c)*conj(z));
}

int GetNumInCircle(const Circle &c)
{
    int count = 0;

    for (int i = 0; i < N; ++i)
    {
        if (norm(allPoints[i]-c.c) <= c.r*c.r)
            ++count;
    }

    return count;
}

int GetNumContained(int p1, int p2)
{
    vector<Point> inter;
    line_circ_inter(Circle(allPoints[p1], Radius), Circle(allPoints[p2], Radius), inter);

    int best = 0;
    for (int i = 0; i < inter.size(); ++i)
    {
        best = max(best, GetNumInCircle(Circle(inter[i], Radius)));
    }

    return best;
}

int main()
{
    int T;
    cin >> T;
    cin.ignore();

    string sep;
    getline(cin, sep);
    sep = "";
    
    while (T--)
    {
        N = 0;

        string line;
        while (getline(cin, line) && line != "")
        {
            stringstream ss(line);
            double x, y;
            ss >> x >> y;
            allPoints[N++] = Point(x, y);
        }

        int best = 1;
        for (int i = 0; i < N; ++i)
        {
            for (int j = i + 1; j < N; ++j)
            {
                best = max(best, GetNumContained(i, j));
            }
        }

        cout << sep << best << '\n';
        sep = "\n";
    }
}
