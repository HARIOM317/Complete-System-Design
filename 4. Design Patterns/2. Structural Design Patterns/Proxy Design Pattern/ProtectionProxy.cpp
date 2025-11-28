#include <iostream>
#include <string>

using namespace std;

class File
{
public:
    virtual void read() = 0;
    virtual ~File() {}
};

class RealFile : public File
{
    string filename;

public:
    RealFile(string fname) : filename(fname) {}

    void read() override
    {
        cout << "Reading file: " << filename << endl;
    }
};

class FileProxy : public File
{
    RealFile *realFile;
    string filename;
    bool isAdmin;

public:
    FileProxy(string fname, bool admin) : filename(fname), isAdmin(admin), realFile(nullptr) {}

    void read() override
    {
        if (!isAdmin)
        {
            cout << "Access Denied! Admin rights required.\n";
            return;
        }

        if (realFile == nullptr)
        {
            realFile = new RealFile(filename);
        }

        realFile->read();
    }

    ~FileProxy()
    {
        delete realFile;
    }
};

int main()
{
    File *userFile = new FileProxy("secret.txt", false);
    userFile->read();

    File *adminFile = new FileProxy("secret.txt", true);
    adminFile->read();

    delete userFile;
    delete adminFile;

    return 0;
}