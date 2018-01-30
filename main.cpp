#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    string filename = argv[1];
    ifstream input(argv[1]);
    if (!input.good() )
    {
        cerr << "Error opening '" << filename << "'. Bailing out.\n";
    }

    string sequence;
    string line;
    vector<string> headers;
    vector<string> sequences;
    while (getline(input,line).good() )
    {
        if (line[0] == '>')
        {
//            cout << "Found Header: " << line << endl;
            if (sequence.empty() )
            {
//                cout << "\"sequence\" is empty!" << endl;
                headers.push_back(line.substr(1, line.size() -1    )   );
            }
            else
            {
//                cout << "\"sequence\" is not empty!" << endl;
//                cout << sequence << endl;
                sequence.append("J");
                sequences.push_back(sequence);
                sequence.clear();
//                cout << sequence << endl;
                headers.push_back(line.substr(1, line.size() - 1   )   );
            }
        }
        else if (!line.empty() && line[0] != '>')
        {
            sequence += line;
        }
    }
    if (sequence != "")
    {
        sequences.push_back(sequence);
    }

//    for (unsigned int i = 0; i < headers.size(); ++i)
//    {
//        cout << headers[i] << endl << sequences[i] << endl;
//    }

    for (unsigned int i = 0; i < headers.size(); ++i)
    {
        ofstream out;
        string outname = headers[i];
        outname.append(".txt");
        out.open(outname);
        out << ">" << headers[i] << endl;
        int pos = 0;
        for (string::iterator strint = sequences[i].begin(); strint != sequences[i].end(); ++strint)
        {
            if (*strint == '-')
            {
                continue;
            }
            else
            {
                out << *strint;
                ++pos;
                if (pos % 60 == 0)
                {
                out << endl;
                }
            }

        }
        out << endl;
        out.close();
    }

    return 0;
}
