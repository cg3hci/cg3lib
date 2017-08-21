#ifndef CG3_FILE_CONVERSIONS_H
#define CG3_FILE_CONVERSIONS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

namespace cg3 {

namespace FileConversions {
    void objToOff(const char* f1, const char* f2);

    void offToObj(const char* f1, const char* f2);

}

inline void FileConversions::objToOff(const char *f1, const char *f2){
    std::ifstream fObj;
    std::ofstream fOff;
    std::istringstream iss;
    std::ostringstream oss;
    std::string line;
    std::string temp;
    int n;

    int nVertices=0;
    int nFaces=0;

    fObj.open(f1);
    fOff.open(f2);

    fOff<<"OFF"<<std::endl;

    while(std::getline(fObj,line))
    {
        iss=std::istringstream(line);

        iss>>temp;

        if(temp[0]=='v')
        {
            nVertices++;
            getline(iss,temp);
            oss<<temp<<" "<<std::endl;
        }
        if(temp[0]=='f')
        {
            nFaces++;
            iss>>n;
            oss<<"3 "<<n-1<<" ";
            iss>>n;
            oss<<n-1<<" ";
            iss>>n;
            oss<<n-1<<" "<<std::endl;
        }

    }
    fOff<<nVertices<<" "<<nFaces<<" 0"<<std::endl;

    fOff<<oss.str();

    fObj.close();
    fOff.close();
}

inline void FileConversions::offToObj(const char *f1, const char *f2){
    std::ofstream fObj;
    std::ifstream fOff;
    std::string line;
    std::istringstream iss;
    std::string temp;

    int nVertices=-1, nFaces=-1;
    double n;

    fOff.open(f1);
    fObj.open(f2);

    while(std::getline(fOff,line))
    {
        iss=std::istringstream(line);
        iss>>temp;

        if((temp.compare("OFF")==0)||(temp[0]=='#')) continue;

        if((nVertices==-1)||(nFaces==-1))
        {
            nVertices=atoi(temp.c_str());
            iss>>nFaces;
            break;
        }
    }

    std::cout<<nVertices<<" "<<nFaces<<std::endl;
    for(int i=0;i<nVertices;++i)
    {
        getline(fOff,line);
        iss=std::istringstream(line);
        getline(iss,temp);
        fObj<<"v "<<temp<<std::endl;
    }

    for(int i=0;i<nFaces;++i)
    {
        getline(fOff,line);
        iss=std::istringstream(line);

        iss>>n;
        iss>>n;
        fObj<<"f "<<n+1<<" ";
        iss>>n;
        fObj<<n+1<<" ";
        iss>>n;
        fObj<<n+1<<std::endl;
    }

    fObj.close();
    fOff.close();
}

}

#endif // CG3_FILE_CONVERSIONS_H
