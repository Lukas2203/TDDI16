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
#include <map>

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

    for (int i = 0; i < N-3; ++i) // i = 
    {
        map<double, vector<Point>> matches; //store matches for point i
        for (int j = i + 1; j < N; ++j) // j = 
        {
            matches[points.at(i).slopeTo(points.at(j))].push_back(points.at(j)); //add the slope from i to j and push pont j to the vector
        }
        for (auto it = matches.begin(); it != matches.end(); ++it) //for every object in matches
        {
            if (it->second.size() >= 3) //if there are lines with three or more points 
            {
                it->second.push_back(points.at(i)); //add point i
                sort(it->second.begin(), it->second.end()); //sort points in the vector to draw from "smallest" to "biggest"
                //render_line(screen, it->second.front(), it->second.back());
                window->draw(it->second.front(), it->second.back()); //draw line
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
