/// @file
/// correction des fichiers in

#include <boost/scoped_array.hpp>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "kernel/DbiteException.h"
#include "kernel/DbiteFile.h"

using namespace boost;
using namespace pacpus;
using namespace std;

int main(int argc, char * argv[])
{
    if (argc < 2) {
        cout << "manque le parametre de nom " << endl;
        cout << "press a key to exit" << endl;
        char c;
        cin >> c;
        exit(0);
    }
    string name = argv[1];
    road_time_t time, t_old;
    road_timerange_t tr;

    DbiteFile in;
    try {
        in.open(name, ReadMode);
    } catch (DbiteException & e) {
        cout << "Error when opening file: " << name << endl;
        cout << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
    cout << "Input file header:\n" << (string) in << endl;


    DbiteFile out;
    {
        string outputFilePath = "out.dbt";
        out.open(outputFilePath, WriteMode, in.getType(), in.getRecordSize());
    }

    size_t size = in.getRecordSize();
    scoped_array<char> data(new char[size]);

    bool first = true;
    for (;;) {
        if (!in.readRecord(time, tr, data.get(), size)) {
            break;
        }
        if (first) {
            t_old = time;
            first = false;
        }

        road_time_diff_t delta = time - t_old;
        cout << "delta: " << delta << " - ";

        if (delta > 10e6) {
            break;
        }
        out.writeRecord(time, tr, data.get(), size); // sizeof(data.get())
        t_old = time;
    }

    return EXIT_SUCCESS;
}
