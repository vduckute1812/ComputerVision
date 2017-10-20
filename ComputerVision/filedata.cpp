#include "filedata.h"

string intToString(int number){
    std::stringstream ss;
    ss << number;
    return ss.str();
}


fileData::fileData()
{
    for(int i=0; i<7; ++i)
        this->Hu[i]= 0;
    this->id = "0";
}

fileData::fileData(double hu_value[], string id){
    for(int i=0; i<7; ++i)
        this->Hu[i]= hu_value[i];
    this->id = id;
}

void fileData::write(FileStorage &fs) const{
    fs << "{"<<"id" << this->id << "Hu0"<<Hu[0] << "Hu1" << Hu[1] << "Hu2" << Hu[2]
        << "Hu3" <<Hu[3] << "Hu4" << Hu[4] << "Hu5" <<Hu[5] << "Hu6" <<Hu[6]<<"}";
}

void fileData::read(const FileNode &node){
    this->id = (string)node["id"];
    for(int i=0; i<6; ++i)
        this->Hu[i] = (double)node["Hu"+intToString(i)];
}

//These write and read functions must be defined for the serialization in FileStorage to work
static void write(FileStorage& fs, const std::string&, const fileData& x)
{
    x.write(fs);
}
static void read(const FileNode& node, fileData& x, const fileData& default_value){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

// This function will print our custom class to the console
static ostream& operator<<(ostream& out, const fileData& m)
{
    out << "{ id = " << m.id << ", ";
    out << "Hu = ";
    for(int i=0; i<7;++i){
        out<<m.Hu[i]<<"";
    }
    out<<"}";
    return out;
}

void writeData(double hu_value[], string id){


}
