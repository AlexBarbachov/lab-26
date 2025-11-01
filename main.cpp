#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;

// read file
vector<string> read_file(const string& filename)
{
    ifstream fin(filename);
    vector<string> data;
    string line;

    while (getline(fin, line))
        data.push_back(line);
    return data;
}


int main() {
    const int numStuff = 20000;
    const int numRaces = 15;

    vector<string> lines = read_file("codes.txt");

    // times = [num races][operation][containers]

    // numRaces = trial number
    // operation -> 4 race types -> read,sort,insert,delete
    // container -> vector, list, set
    // cube slicing represnets reach individuals race's container's timing.
    long long times[numRaces][4][3];

  


    // populate our 3D array by looping through the tests 15 times.
    for (int i = 0; i < numRaces; i++)
    {
        // ********************* RACE 1 *************************
        // vector!!
        {
            clock_t start = clock();
            vector<string> v;
            for (size_t i = 0; i < lines.size(); i++)
            {
                v.push_back(lines[i]);
            }
            clock_t end = clock();
            times[i][0][0] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        // list!!
        {
            clock_t start = clock();
            list<string> l;

            for (size_t i = 0; i < lines.size(); i++)
                l.push_back(lines[i]);
                
            clock_t end = clock();
            times[i][0][1] = (long long)(long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        // set!!
        {
            clock_t start = clock();
            set<string> s;

            for (size_t i = 0; i < lines.size(); i++)
                s.insert(lines[i]);
                
            clock_t end = clock();
            times[i][0][2] = (long long)(long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }


        // ********************* RACE 2 *************************
        {
            vector<string> v = lines;
            clock_t start = clock();
            sort(v.begin(), v.end());
            clock_t end = clock();
            times[i][1][0] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        {
            list<string> l(lines.begin(), lines.end());
            clock_t start = clock();
            l.sort();
            clock_t end = clock();
            times[i][1][1] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        {
            times[i][1][2] = -1; // set is alr sorted
        }


        // ********************* RACE 3 *************************
        {
            vector<string> v = lines;
            clock_t start = clock();

            v.insert(v.begin() + v.size()/2, "abc");
            clock_t end = clock();
            times[i][2][0] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        {
            list<string> l(lines.begin(), lines.end());


            clock_t start = clock();
            list<string>::iterator it = l.begin();
            for (size_t i = 0; i < l.size()/2; ++i) ++it;
            l.insert(it, "TESTCODE");
            clock_t end = clock();
            times[i][2][1] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
            
        }

        {
            set<string> s(lines.begin(), lines.end());
            clock_t start = clock();
            s.insert("TESTCODE");
            clock_t end = clock();
            times[i][2][2] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        // ********************* RACE 4 *************************
        {
            vector<string> v = lines;
            clock_t start = clock();
            v.erase(v.begin() + v.size()/2);
            clock_t end = clock();
            times[i][3][0] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        {
            list<string> l(lines.begin(), lines.end());
            list<string>::iterator it = l.begin();
            clock_t start = clock();
            for (size_t i = 0; i < l.size()/2; ++i) ++it;

            l.erase(it);
            clock_t end = clock();
            times[i][3][1] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }

        {
            set<string> s(lines.begin(), lines.end());
            set<string>::iterator it = s.begin();
            clock_t start = clock();
            for (size_t i = 0; i < s.size()/2; ++i) ++it;

            s.erase(it);
            clock_t end = clock();
            times[i][3][2] = (long long)((end - start) * 1000000 / CLOCKS_PER_SEC);
        }
    }


    // output
    cout << "\nNumber of Simulations: " << numRaces << endl;

    cout << left << setw(12) << "Operation" << setw(12) << "Vector" << setw(12) << "List" << setw(12) << "Set" << endl;

    const char* names[4] = {"Read", "Sort", "Insert", "Delete"};


    // triple loop to get each value averaged
    for (int i = 0; i < 4; i++)
    {
        cout << left << setw(12) << names[i];
        for (int j = 0; j < 3; j++)
        {
            long long total = 0;
            for (int k = 0; k < numRaces; k++)
            {
                total += times[k][i][j]; // find the sum of all times for the specific race and container
            }
            cout << setw(12) << total / numRaces; // avg time and output it
        }
        cout << endl;
    }

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/

