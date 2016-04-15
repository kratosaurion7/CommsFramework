#include <XFile.h>
#include <PackageFile.h>
#include <IOUtilities.h>

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
    
    fil->AddDirectory(dir);

    fil->Save("out.pak");

    delete(fil);
    allFiles->Release();
    delete(allFiles);
    delete(dir);

    return 0;
}