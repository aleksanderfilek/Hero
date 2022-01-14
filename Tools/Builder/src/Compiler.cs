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
    public static void run(string startDir, Config? config, List<string> headerFiles, List<string> sourceFiles)
    {
        Stopwatch stopWatch = new Stopwatch();
        stopWatch.Start();
        List<string> objectFiles = compile(startDir, config, headerFiles, sourceFiles);
        stopWatch.Stop();
        TimeSpan compileT = stopWatch.Elapsed;

        stopWatch = new Stopwatch();
        stopWatch.Start();
        link(startDir, objectFiles, config);
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
            string? path = Path.GetDirectoryName(inc);
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

    private static string combineStringArr(string[]? arr)
    {
        StringBuilder builder = new StringBuilder();
        foreach(string? str in arr)
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

    private static List<string> compile(string? startDir, Config? config, 
        List<string> headerFiles, List<string> sourceFiles)
    {
        Console.WriteLine("Compiling");

        string incArg = constructIncludes(headerFiles);
        string definesArg = combineStringArr(config.Defines);
        string debugArg = constructDebug(config.Debug);
        string? objPath = startDir + "obj";
        string typeArg="";
        if(config.Type.CompareTo("SharedLibrary")==0)
        {
            typeArg = "-fPIC";
        }
        List<string> objFiles = new List<string>();
        List<string?> errors = new List<string?>();

        foreach(string src in sourceFiles)
        {
            StringBuilder builder = new StringBuilder();

            string? relativePath = src.Replace(Path.Combine(startDir, "src/"), "");
            string? relativePathO = relativePath.Split(".")[0];
            string? fullObjPath = objPath + "/" + relativePathO + ".o";

            if(!Directory.Exists(Path.GetDirectoryName(fullObjPath)))
            {
                Directory.CreateDirectory(Path.GetDirectoryName(fullObjPath));
            }

            builder.AppendFormat("-c {0} {1} {2} {3} -o {4} {5}", 
                debugArg, definesArg, incArg, src, fullObjPath, typeArg);
            objFiles.Add(fullObjPath);

            Console.Write("Compiling: {0} - ", relativePath);

            ProcessStartInfo pStartInfo = new ProcessStartInfo();

            pStartInfo.FileName = config.Compiler;
            pStartInfo.Arguments = builder.ToString();
            pStartInfo.UseShellExecute = false;

            pStartInfo.RedirectStandardError  = false;
            pStartInfo.RedirectStandardOutput = false;

            bool status = true;
            Process proc = new Process();
            proc.StartInfo = pStartInfo;
            proc.ErrorDataReceived += new DataReceivedEventHandler((sender, e) => 
            { 
                errors.Add(e.Data); 
                status = false;
            });

            proc.Start();
            proc.WaitForExit();

            if(status)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("OK");
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("FAILED");
            }
            Console.ResetColor();
        }

        return objFiles;
    }

    private static void link(string? startDir,List<string> objectFiles, Config? config)
    {
        Console.WriteLine("Linking");

        string outPath = Path.Combine(startDir, config.OutputDir);
        if(!Directory.Exists(outPath))
        {
            Directory.CreateDirectory(outPath);
        }

        string definesArg = combineStringArr(config.Defines);
        string debugArg = constructDebug(config.Debug);
        string objFileArg = combineStringList(objectFiles);
        string libsDirArg = combineStringArr(config.LibsDir);
        string libsArg = combineStringArr(config.Libs);
        string typeArg = "";
        if(config.Type.CompareTo("SharedLibrary")==0)
        {
            typeArg = "-shared";
        }

        StringBuilder builder = new StringBuilder();
        builder.AppendFormat("{0} {1} {2} {3} -o {4}/{5}{6} {7} {8}", 
            definesArg, debugArg, libsDirArg, objFileArg, outPath, config.Name, config.Extension, libsArg, typeArg);

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