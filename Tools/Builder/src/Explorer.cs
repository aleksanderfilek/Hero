using System.IO;

namespace Builder
{

class Explorer
{
    public static void run(String startDir, out List<string> headerFiles, out List<string> sourceFiles)
    {
        headerFiles = new List<string>();
        sourceFiles = new List<string>();

        wander(startDir, ref headerFiles, ref sourceFiles);
    }

    private static void wander(String curDir, ref List<string> headerFiles, ref List<string> sourceFiles)
    {
        string [] files = Directory.GetFiles(curDir);
        foreach(string file in files)
        {
            string extension = Path.GetExtension(file);
            if(extension.CompareTo(".hpp") == 0 || extension.CompareTo(".h") == 0)
            {
                headerFiles.Add(file);
            }
            else if(extension.CompareTo(".cpp") == 0 || extension.CompareTo(".c") == 0)
            {
                sourceFiles.Add(file);
            }
        }

        string [] subDirs = Directory.GetDirectories(curDir);
        foreach(string subDir in subDirs)
        {
            wander(subDir, ref headerFiles, ref sourceFiles);
        }
    }
}

}