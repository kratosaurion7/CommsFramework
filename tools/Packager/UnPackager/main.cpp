#include <XFile.h>
#include <PackageFile.h>
#include <IOUtilities.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }
    
    char* pakPath = argv[1];

    bool pathIsFile = IsValidFilePath(pakPath);

    if (pathIsFile)
    {
        PackageFile package = PackageFile(pakPath);

        package.Extract("");
    }    

    return 0;
}