#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include <boost/serialization/access.hpp>
#include <tablehandler.cpp>

using namespace std;

vector<string> removeDupWord(string str)
{
    vector<string> results;
    // boost::split(results, str, [](char c) { return c == ' '; });
    boost::split(results, str, boost::is_any_of("-"));

    return results;
}

int main()
{
    DatabaseApp dbApp;
    string command;
    Database *workingDatabase;

    ifstream ifs("databasedata.dbd", ios::binary);
    boost::archive::text_iarchive ia(ifs);
    ia >> dbApp;
    ifs.close();

    while (true)
    {

        cout << "commands \n";
        cin >> command;

        vector<string> commandWords;
        // commandWords.push_back(command);

        commandWords = removeDupWord(command);

        if (command.substr(0, 3) == "use" && commandWords.size() == 2)
        {
            try
            {
                workingDatabase = &dbApp.getDatabase(commandWords[1]);
            }
            catch (exception e)
            {
                cout << e.what() << endl;
            }
            catch (char const *msg)
            {
                cout << msg << endl;
            }
        }
        if (workingDatabase != nullptr)
        {
            if (command.substr(0, 12) == "create-table" && commandWords.size() >= 5)
            {
                string tableName = commandWords[2];
                vector<string> columns;
                vector<string> types;

                for (int i = 0; i < commandWords.size(); i++)
                {
                    if (i <= 3)
                        continue;
                    else
                    {
                        if (i % 2 == 0)
                        {
                            columns.push_back(commandWords[i]);
                        }
                        else
                        {
                            types.push_back(commandWords[i]);
                        }
                    }
                }

                try
                {
                    Table newTable(tableName, columns, types);
                    workingDatabase->addTable(newTable);
                }
                catch (exception e)
                {
                    cout << e.what() << endl;
                }
                catch (char const *msg)
                {
                    cout << msg << endl;
                }
            }
            else if (command.substr(0, 12) == "delete-table" && commandWords.size() == 3)
            {
                try
                {
                    workingDatabase->removeTable(commandWords[2]);
                }
                catch (exception e)
                {
                    cout << e.what() << endl;
                }
                catch (char const *msg)
                {
                    cout << msg << endl;
                }
            }
            else if (command.substr(0, 12) == "select-table" && commandWords.size() >= 3)
            {
                try
                {
                    workingDatabase->getTable(commandWords[2]).showTable();
                }
                catch (exception e)
                {
                    cout << e.what() << endl;
                }
                catch (char const *msg)
                {
                    cout << msg << endl;
                }
            }
            else if (command.substr(0, 12) == "insert-table" && commandWords.size() >= 3)
            {
                vector<string> temp;
                temp.insert(temp.begin(), commandWords.begin() + 3, commandWords.end());
                try
                {
                    workingDatabase->getTable(commandWords[2]).addData(temp);
                }
                catch (exception e)
                {
                    cout << e.what() << endl;
                }
                catch (char const *msg)
                {
                    cout << msg << endl;
                }
            }
            else if (command.compare("save") == 0)
            {
                ofstream ofs("databasedata.dbd");
                boost::archive::text_oarchive oa(ofs);
                oa << workingDatabase;
                ofs.close();
            }else if(command.compare("exit") == 0){
                break;
            }
            else
            {
                cout << "command not found";
            }
        }
        else
        {
            cout << "Please choose a database to work on first !!" << endl;
        }
    }
}