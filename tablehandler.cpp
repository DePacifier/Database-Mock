#include <iostream>
#include <boost/serialization/access.hpp>
#include <vector>

using namespace std;

class Table
{
    // Access specifier
public:
    // Data Members
    int tableColumnSize;
    vector<string> tableColumns;
    vector<string> tableTypes;
    string tableName;
    vector<vector<string>> tableRepresentation;
    int tableDataCount = tableRepresentation.size();

    Table(string name, vector<string> columns, vector<string> types)
    {
        createTable(name, columns, types);
    }

    void createTable(string name, vector<string> columns, vector<string> types)
    {
        vector<vector<string>> newTable;

        tableColumns = columns;
        tableTypes = types;
        tableColumnSize = columns.size();
        tableName = name;
        tableRepresentation = newTable;
    }

    // Member Functions()
    void addData(vector<string> data)
    {
        if (data.size() <= tableColumnSize)
        {
            tableRepresentation.push_back(data);
        }
        throw "Invalid Column Size";
    }

    void showTable()
    {
        for (int i = 0; i < tableRepresentation.size(); i++)
        {
            for (int j = 0; j < tableRepresentation[i].size(); j++)
            {
                cout << tableRepresentation[i][j] << " ";
            }
            cout << endl;
        }
    }

    Table intersectTable(Table otherTable)
    {
        if (tableColumnSize == otherTable.tableColumnSize)
        {
            string tableName = tableName + "-intersect-" + otherTable.tableName;
            Table newTable(tableName, tableColumns, tableTypes);

            int size = tableRepresentation.size();
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < otherTable.tableRepresentation.size(); j++)
                {
                    if (tableRepresentation[i] == otherTable.tableRepresentation[j])
                    {
                        newTable.addData(tableRepresentation[i]);
                    }
                }
            }

            return newTable;
        }

        throw "Tables can not be intersected";
    }

    Table joinTable(Table otherTable)
    {
        string tableName = tableName + "-union-" + otherTable.tableName;
        vector<string> newtableColumns;
        vector<string> newtableTypes;
        newtableColumns.insert(newtableColumns.begin(), tableColumns.begin(), tableColumns.end());
        newtableColumns.insert(newtableColumns.end(), otherTable.tableColumns.begin(), otherTable.tableColumns.end());

        newtableTypes.insert(newtableTypes.begin(), tableTypes.begin(), tableTypes.end());
        newtableTypes.insert(newtableTypes.end(), otherTable.tableTypes.begin(), otherTable.tableTypes.end());

        Table newTable(tableName, newtableColumns, newtableTypes);

        for (int i = 0; i < tableDataCount; i++)
        {
            newTable.addData(tableRepresentation[i]);
        }

        for (int i = 0; i < otherTable.tableDataCount; i++)
        {
            newTable.addData(otherTable.tableRepresentation[i]);
        }

        return newTable;
    }

    Table differentiateTable(Table otherTable)
    {
        if (tableColumnSize == otherTable.tableColumnSize)
        {
            string tableName = tableName + "-differntiate-" + otherTable.tableName;
            Table newTable(tableName, tableColumns, tableTypes);

            for (int i = 0; i < tableDataCount; i++)
            {
                for (int j = 0; j < otherTable.tableDataCount; j++)
                {
                    if (tableRepresentation[i] != otherTable.tableRepresentation[j])
                    {
                        newTable.addData(tableRepresentation[i]);
                    }
                }
            }

            return newTable;
        }
    }

    Table cartesianProductTable(Table otherTable)
    {
        string tableName = tableName + "-cartesian-" + otherTable.tableName;
        vector<string> newtableColumns;
        vector<string> newtableTypes;
        newtableColumns.insert(newtableColumns.begin(), tableColumns.begin(), tableColumns.end());
        newtableColumns.insert(newtableColumns.end(), otherTable.tableColumns.begin(), otherTable.tableColumns.end());

        newtableTypes.insert(newtableTypes.begin(), tableTypes.begin(), tableTypes.end());
        newtableTypes.insert(newtableTypes.end(), otherTable.tableTypes.begin(), otherTable.tableTypes.end());

        Table newTable(tableName, newtableColumns, newtableTypes);

        for (int i = 0; i < tableDataCount; i++)
        {
            for (int j = 0; j < otherTable.tableDataCount; j++)
            {
                vector<string> temp;
                temp.insert(temp.begin(), tableRepresentation[i].begin(), tableRepresentation[i].end());
                temp.insert(temp.end(), otherTable.tableRepresentation[i].begin(), otherTable.tableRepresentation[i].end());
                newTable.addData(temp);
            }
        }

        return newTable;
    }
};

class Database
{
    // Access specifier
public:
    // Data Members
    string databaseName;
    vector<Table> tables;

    Database(string name)
    {
        databaseName = name;
    }

    // Member Functions()
    void addTable(Table newTable)
    {
        tables.push_back(newTable);
    }

    Table getTable(string tableName)
    {
        for (int i = 0; i < tables.size(); i++)
        {
            if (tables[i].tableName.compare(tableName) == 0)
            {
                return tables[i];
            }
        }

        throw "Table Not Found";
    }

    void showTables()
    {
        for (int i = 0; i < tables.size(); i++)
        {
            cout << tables[i].tableName << endl;
        }
    }

    // check again
    void removeTable(string tableName)
    {
        for (int i = 0; i < tables.size(); i++)
        {
            if (tables[i].tableName.compare(tableName) == 0)
            {
                tables.erase(tables.begin() + i);
            }
        }

        throw "Table Not Found";
    }
};

class DatabaseApp
{
    // Access specifier
private:

friend class boost::serialization::access;
template<class Archive>
void serialize(Archive & dbs, const unsigned int version){
    dbs & databases;
}
vector<Database> databases;
public:
    // Data Members
    DatabaseApp();
    

    // Member Functions()
    void addDatabase(Database newDatabase){
        databases.push_back(newDatabase);
    }

    Database getDatabase(string databaseName)
    {
        for (int i = 0; i < databases.size(); i++)
        {
            if (databases[i].databaseName.compare(databaseName) == 0)
            {
                return databases[i];
            }
        }

        throw "Database Not Found";
    }

    void showDatabases()
    {
        for (int i = 0; i < databases.size(); i++)
        {
            cout << databases[i].databaseName << endl;
        }
    }

    // check again
    void removeDatabase(string databaseName)
    {
        for (int i = 0; i < databases.size(); i++)
        {
            if (databases[i].databaseName.compare(databaseName) == 0)
            {
                databases.erase(databases.begin() + i);
            }
        }

        throw "Database Not Found";
    }

    
};

int main()
{
    Database db("mydb");
    Table tables("student", {"Name", "Age"}, {"string", "int"});
    Table tableh("hippy", {"Name", "Age"}, {"string", "int"});
    Table tableb("boss", {"Name", "Age"}, {"string", "int"});

    db.addTable(tables);
    db.addTable(tableh);
    db.addTable(tableb);

    cout << db.databaseName << endl;
    db.showTables();

    //db.getTable("student");
    //db.getTable("me");

    db.removeTable("hippy");
    cout << "remove table student" << endl;
    db.showTables();
}
