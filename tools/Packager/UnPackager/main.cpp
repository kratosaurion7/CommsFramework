#include <XFile.h>
#include <PackageFile.h>
#include <EncryptedPackageFile.h>
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
        EncryptedPackageFile package = EncryptedPackageFile("out.pak", "1234");
        
        package.Extract("");
    }    

    return 0;
}