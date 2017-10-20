#ifndef FILEDATA_H
#define FILEDATA_H
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class fileData
{
public:
    fileData();
    explicit fileData(double hu_value[], string id);
    void write(FileStorage& fs) const;
    void read(const FileNode& node);

public:     //Data member
    string id;
    double Hu[7];
};


static void write(FileStorage& fs, const std::string&, const fileData& x);
static void read(const FileNode& node, fileData& x, const fileData& default_value = fileData());
static ostream& operator<<(ostream& out, const fileData& m);
string intToString(int number);
void writeData(double hu_value[], string id);

#endif // FILEDATA_H
