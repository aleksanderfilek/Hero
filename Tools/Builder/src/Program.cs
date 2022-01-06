using System;
using System.Diagnostics;
using System.Collections;
using System.IO;
using System.Text.Json;

namespace Builder
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string? startDir = args[0];
            string? jsonConfig = File.ReadAllText(Path.Combine(startDir, "config.json"));
            Config? config = JsonSerializer.Deserialize<Config>(jsonConfig);

            List<string> headerFiles;
            List<string> sourceFiles;
            Explorer.run(startDir, out headerFiles, out sourceFiles);

            if(sourceFiles.Count == 0) return;

            Compiler.run(startDir, config, headerFiles, sourceFiles);

        }
    }
}