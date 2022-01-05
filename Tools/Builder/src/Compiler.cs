using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System;
using System.Diagnostics;

namespace Builder
{

class Compiler
{
    public static void run(string startDir, Config config, List<string> headerFiles, List<string> sourceFiles)
    {
        Stopwatch stopWatch = new Stopwatch();
        stopWatch.Start();
        List<string> objectFiles = compile(startDir, config, headerFiles, sourceFiles);
        stopWatch.Stop();
        TimeSpan compileT = stopWatch.Elapsed;

        stopWatch = new Stopwatch();
        stopWatch.Start();
        link(objectFiles, config);
        stopWatch.Stop();
        TimeSpan linkT = stopWatch.Elapsed;

        string compileTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            compileT.Hours, compileT.Minutes, compileT.Seconds,
            compileT.Milliseconds / 10);
        string linkTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            linkT.Hours, linkT.Minutes, linkT.Seconds,
            linkT.Milliseconds / 10);
        Console.WriteLine("Time");
        Console.WriteLine("Compilation: " + compileTime);
        Console.WriteLine("Link: " + linkTime);
    }

    private static string constructIncludes(List<string> headerFiles)
    {
        HashSet<string> incSet = new HashSet<string>();
        foreach(string inc in headerFiles)
        {
            if(inc == null) continue;
            string path = Path.GetDirectoryName(inc);
            if(path == null) continue;
            incSet.Add(path);
        }

        StringBuilder builder = new StringBuilder();
        foreach(string inc in incSet)
        {
            builder.AppendFormat("-I{0} ", inc);
        }

        return builder.ToString();
    }

    private static string constructSources(List<string> sourceFiles)
    {
        StringBuilder builder = new StringBuilder();
        foreach(string src in sourceFiles)
        {
            builder.AppendFormat("{0} ", src);
        }

        return builder.ToString();
    }

    private static string combineStringArr(string[] arr)
    {
        StringBuilder builder = new StringBuilder();
        foreach(string str in arr)
        {
            builder.AppendFormat("{0} ", str);
        }

        return builder.ToString();
    }

    private static string combineStringList(List<string> arr)
    {
        StringBuilder builder = new StringBuilder();
        foreach(string str in arr)
        {
            builder.AppendFormat("{0} ", str);
        }

        return builder.ToString();
    }

    private static string constructDebug(bool debug)
    {
        if(debug == true)
        {
            return "-g -DDEBUG";
        }

        return "";
    }

    private static List<string> compile(string startDir, Config config, 
        List<string> headerFiles, List<string> sourceFiles)
    {
        Console.WriteLine("Compiling");

        string incArg = constructIncludes(headerFiles);
        string definesArg = combineStringArr(config.Defines);
        string debugArg = constructDebug(config.Debug);
        string objPath = startDir + "obj";
        List<string> objFiles = new List<string>();
        List<string> errors = new List<string>();

        foreach(string src in sourceFiles)
        {
            StringBuilder builder = new StringBuilder();

            string relativePath = src.Replace(startDir + "src", "");
            string relativePathO = relativePath.Split(".")[0];
            string fullObjPath = objPath + "/" + relativePathO + ".o";

            if(!Directory.Exists(Path.GetDirectoryName(fullObjPath)))
            {
                Directory.CreateDirectory(Path.GetDirectoryName(fullObjPath));
            }

            builder.AppendFormat("-c {0} {1} {2} {3} -o {4} -fPIC", 
                debugArg, definesArg, incArg, src, fullObjPath);
            objFiles.Add(fullObjPath);

            Console.WriteLine("Compiling: " + relativePath);

            ProcessStartInfo pStartInfo = new ProcessStartInfo();

            pStartInfo.FileName = config.Compiler;
            pStartInfo.Arguments = builder.ToString();
            pStartInfo.UseShellExecute = false;

            pStartInfo.RedirectStandardError  = false;
            pStartInfo.RedirectStandardOutput = false;

            Process proc = new Process();
            proc.StartInfo = pStartInfo;
            proc.ErrorDataReceived += new DataReceivedEventHandler((sender, e) => 
                { errors.Add(e.Data); });

            proc.Start();
            proc.WaitForExit();
        }

        return objFiles;
    }

    private static void link(List<string> objectFiles, Config config)
    {
        Console.WriteLine("Linking");

        string definesArg = combineStringArr(config.Defines);
        string debugArg = constructDebug(config.Debug);
        string objFileArg = combineStringList(objectFiles);
        string libsDirArg = combineStringArr(config.LibsDir);
        string libsArg = combineStringArr(config.Libs);

        StringBuilder builder = new StringBuilder();
        builder.AppendFormat("{0} {1} {2} {3} -o {4} {5} -shared", 
            definesArg, debugArg, libsDirArg, objFileArg, config.Name, libsArg);

        ProcessStartInfo pStartInfo = new ProcessStartInfo();

        pStartInfo.FileName = config.Compiler;
        pStartInfo.Arguments = builder.ToString();
        pStartInfo.UseShellExecute = false;

        pStartInfo.RedirectStandardError  = false;
        pStartInfo.RedirectStandardOutput = false;

        Process proc = new Process();
        proc.StartInfo = pStartInfo;
        proc.Start();
        proc.WaitForExit();
    }
}

}