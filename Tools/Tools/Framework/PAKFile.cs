using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Tools.Framework
{
    public class PAKFile
    {
        private string HeaderSignature = "PACK"; // 4 bytes

        private int DirectoryOffset; // 4 Bytes

        private int DirectoryLength; // 4 Bytes

        private PAKFileDirectory PakDirectory;

        private Encoding enc = Encoding.ASCII;

        private const int FILENAME_MAX_LENGTH = 32;


        public PAKFile()
        {
            PakDirectory = new PAKFileDirectory();
        }

        public void AddFile(FileInfo file)
        {
            
        }

        public bool DirectoryFilterPredicate(FileInfo file)
        {
            //if (file.FullName.Contains("Bonus_Falling_Wilds") ||
            //    file.FullName.Contains("Bonus_Mult_Touch") ||
            //    file.FullName.Contains("Free_Games"))
            //{
            //    return false;
            //}


            return true;
        }

        public void AddFiles(IEnumerable<FileInfo> files, DirectoryInfo rootAssetsFolder = null)
        {
            var packDirectory = new List<PackDirectoryEntry>();

            var bytesCount = 0;

            foreach (var file in files)
            {
                var entry = new PackDirectoryEntry();

                if(rootAssetsFolder != null)
                {
                    entry.FileName = file.FullName.Replace(rootAssetsFolder.FullName, "");
                }
                else
                {
                    entry.FileName = file.Name;
                }
                
                entry.FileLength = (int)file.Length;
                entry.FilePosition = bytesCount; // file size + file length + file offset

                entry.FileData = file;

                bytesCount += (int)file.Length;

                packDirectory.Add(entry);
            }

            PakDirectory.AddEntryList(packDirectory);
        }

        public void AddDirectoryFiles(DirectoryInfo dir, Func<FileInfo, bool> fileSelectionPredicate)
        {
            var packDirectory = new List<PackDirectoryEntry>();

            var files = dir.EnumerateFiles("*", SearchOption.AllDirectories).Where(fileSelectionPredicate);

            var bytesCount = 0;

            foreach (var file in files)
            {
                var entry = new PackDirectoryEntry();
                entry.FileName = file.FullName.Replace(dir.FullName, "");
                entry.FileLength = (int)file.Length;
                entry.FilePosition = bytesCount;

                entry.FileData = file;

                bytesCount += (int)file.Length;

                packDirectory.Add(entry);
            }

            PakDirectory.AddEntryList(packDirectory);
        }

        public void Save(FileInfo outputFile)
        {
            RecalculateHeader();

            var outputStream = new FileStream(outputFile.FullName, FileMode.Create);
            var sw = new BinaryWriter(outputStream, Encoding.ASCII);

            // WRITE HEADER
            sw.Write(enc.GetBytes(this.HeaderSignature));
            sw.Write(BinaryHelper.GetBytes(this.DirectoryOffset));
            sw.Write(BinaryHelper.GetBytes(this.DirectoryLength));

            // WRITE DIRECTORY
            foreach (var entry in PakDirectory.files)
            {
                sw.Write(enc.GetBytes(entry.FileName.Replace('\\', '/').PadRight(FILENAME_MAX_LENGTH, '\0'))); // FileName

                sw.Write(BinaryHelper.GetBytes(entry.FilePosition + this.DirectoryOffset + this.DirectoryLength)); // File Position

                sw.Write(BinaryHelper.GetBytes(entry.FileLength)); // File Length
            }

            // WRITE FILES
            foreach (var entry in PakDirectory.files)
            {
                var fileStream = entry.FileData.OpenRead();

                fileStream.CopyTo(sw.BaseStream);

                fileStream.Close();
            }

            sw.Flush();
            sw.Close();

            outputStream.Close();
        }

        private void RecalculateHeader()
        {
            DirectoryOffset = 12;
            DirectoryLength = PakDirectory.GetDirectoryLength();
        }

        private class PAKFileDirectory
        {
            public List<PackDirectoryEntry> files = new List<PackDirectoryEntry>();

            private int bytesOffset;

            private DirectoryInfo _rootDir;

            public PAKFileDirectory() { }

            public PAKFileDirectory(DirectoryInfo directoryRoot)
            {
                _rootDir = directoryRoot;
            }

            public void AddEntry(FileInfo file)
            {
                var entry = new PackDirectoryEntry();
                
                if(_rootDir == null)
                {
                    entry.FileName = file.Name;
                }else{
                    entry.FileName = file.FullName.Replace(_rootDir.FullName, "");
                }

                entry.FileLength = (int)file.Length;
                entry.FilePosition = bytesOffset;
                entry.FileData = file;

                bytesOffset += entry.FileLength;
            }

            public void AddEntryList(IEnumerable<PackDirectoryEntry> newFiles)
            {
                files = newFiles.Concat(files).ToList();

                bytesOffset += files.Aggregate(0, (p, q) => p += q.FileLength);
            }

            public void UpdateEntriesPositions()
            {

            }

            public int GetDirectoryLength()
            {
                return files.Aggregate(0, (p, q) => {
                    var count = 0;

                    count += 4; // FileName 4 bytes
                    count += 4; // FilePosition 4 bytes
                    count += FILENAME_MAX_LENGTH;

                    p += count;

                    return p;
                });
            }

            public int GetDataLength()
            {
                return bytesOffset;
                //return files.Aggregate(0, (p, q) => p += q.FileLength);
            }
        }

        public class PackDirectoryEntry
        {
            public string FileName { get; set; }

            public int FilePosition { get; set; } // Position relative to the directory start

            public int FileLength { get; set; }

            public FileInfo FileData { get; set; }

            public override string ToString()
            {
                return String.Format("{0} : P={1}, L={2}", FileName, FilePosition, FileLength);
            }
        }

    }
}
