/*
 * fast < input.txt
 *
 * Compute and plot all line segments involving 4 points in input.txt
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "point.h"
#include "window.h"
#include <unordered_map>

using namespace std;

int main(int argc, const char *argv[])
{
    WindowPtr window = create_window(argc, argv);

    // The array of points
    vector<Point> points;

    // Read points from cin
    int N{}; //N = Number of points
    cin >> N;

    for (int i{0}; i < N; ++i)
    {
        unsigned int x, y;
        cin >> x >> y;
        points.push_back(Point{x, y});
    }

    // draw points to screen all at once
    window->draw(points);

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());

    auto begin = chrono::high_resolution_clock::now();

    /////////////////////////////////////////////////////////////////////////////
    // Draw any lines that you find in 'points' using the function 'window->draw'.
    /////////////////////////////////////////////////////////////////////////////


    for(Point p : points) //Gå igenom alla punkter
    {
        unordered_map<double, vector<Point>> matches; //map för att spara alla punkter med samma lutning mot p
        Point curr_point{p};
        
        for(Point q : points) //Gå igenom alla punkter igen
        {   
            matches[curr_point.slopeTo(q)].push_back(q); //Räkna ut lutning från p till q
        }
        
        for(pair<double, vector<Point>> match : matches) //gå igenom alla lutningar till alla punkter
        {
            if(match.second.size() >= 3) //Kolla om vi har hittat minst tre andra punkter med samma lutning
            {
                match.second.push_back(p); //Lägg till ursprungspunkten (p)
                window->draw(match.second.front(),match.second.back()); //skriv ut linje
            }
            
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // wait for user to terminate program
    window->run();

    return 0;
}
