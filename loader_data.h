#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template<typename Data>

Data getAllData( string nameEntity ){
    try
    {
        ifstream file(nameEntity);
        string line;

        if( !file.is_open() ){
            throw exception() ;
        }

        while( getline( file, line ) ){
            cout << line << endl;
        }

    }
    catch(const exception& e)
    {
        cerr << "No se pudo abrir el archivo" << "\n";
    }
    
}

bool updateAllData( string nameEntity ){
    
}