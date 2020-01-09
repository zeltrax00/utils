#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <Shlwapi.h>
using namespace std;

// Parsing a string into arguments for monitoring create process phase.
vector<wstring> CmdLineParser(wstring wsCmdLine)
{
    vector<wstring> v;
    int argc = 0;
    LPWSTR *argv = CommandLineToArgvW(wsCmdLine.c_str(), &argc);
    for (size_t i = 0; i < argc; ++i)
    {
        wprintf(L"[+] argv[%d]: %s\n", i, argv[i]);
    }

    size_t i = 0;
    while (i < argc)
    {
        if (PathFileExistsW(argv[i]) &&
            !PathIsDirectoryW(argv[i]))
        {
            v.push_back(argv[i]);
        }
        else
        {
            size_t oi = i;
            wstring temp = argv[i];
            while (!PathFileExistsW(temp.c_str()) || PathIsDirectoryW(temp.c_str()))
            {
                if (i < argc - 1)
                {
                    temp += L" ";
                    temp += argv[++i];
                }
                else if (oi == argc - 1)
                {
                    break;
                }
                else
                {
                    size_t space = temp.find(L' ', 0);
                    v.push_back(temp.substr(0, space));
                    i = ++oi;
                    temp = argv[i];
                }
            }
            v.push_back(temp);
        }
        ++i;
    }
    puts("---Result:");
    for (size_t j = 0; j < v.size(); ++j)
    {
        wprintf(L"[+] v[%d]: %s\n", j, v[j].c_str());
    }
    return v;
}

int main()
{
    wstring cmd;
    vector<wstring> v;
    while (1)
    {
        cout << "\nCMD: ";
        getline(wcin, cmd);
        v = CmdLineParser(cmd);
        v.clear();
    }
}
