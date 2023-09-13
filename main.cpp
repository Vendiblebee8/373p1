#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <getopt.h>
#include <stdlib.h>
#include "parser.h"
#include <vector>
#include <bits/stdc++.h>



bool fileOpen(string file, ifstream &fileObj)
{
    fileObj.open(file);
    if (fileObj.is_open())
    {
        return true;
    }
    else
    {
        cout << "does not open" << endl;
        return false;
    }
}

void readFileS(string file, ifstream &fileObj)
{
    int setF = 0;
    string line;
    string name;
    string buyP;
    int setN;
    string sellP;
    while (getline(fileObj, line))
    {
        name = "";
        buyP = -1;
        setN = 0;
        sellP = -1;
        stringstream ss(line);
        getline(ss, name, ' ');
        getline(ss, sellP, ' ');
        try
        {
            numS = +stoi(name);
        }
        catch (std::invalid_argument const &ex)
        {
            if (card.readS(name, sellP))
            {
                sell.push_back(card);
            }
        }
    }
}
