#include <XFile.h>
#include <PackageFile.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    char* dirPath = argv[1];

    XDirectory* dir = new XDirectory(dirPath);

    auto allFiles = dir->GetFiles(true);

    PackageFile* fil = new PackageFile();
    
    // fil.AddDirectory(dir);

    for (int i = 0; i < allFiles->Count(); i++)
    {
        std::string filePath = allFiles->Get(i)->FilePath;

        fil->AddFile(filePath);
    }

    fil->Save("Out.pak");

    delete(fil);
    allFiles->Release();
    delete(allFiles);
    delete(dir);

    return 0;
}