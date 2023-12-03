using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AoC_day2
{
    internal class Task1
    {
        public void execute()
        {
            StreamReader sr = new StreamReader("../../../input.txt");
            var line = sr.ReadLine();
            int lineCount = 0;
            int finalSum = 0;
            bool isCorrect = true;
            while (line != null)
            {
                ++lineCount;
                line = line.Substring(line.IndexOf(": ") + 2);
                var sets = line.Split(";");
                foreach ( var setString in sets)
                {
                    var set = new Set(setString);
                    isCorrect = isCorrect & set.test();
                }
                finalSum = isCorrect? finalSum + lineCount : finalSum;
                isCorrect = true;
                line = sr.ReadLine();
            }
            Console.WriteLine(finalSum);
        }
    }

    internal class Task2
    {
        public void execute()
        {
            List<Set> gamesMinimums = new List<Set>();
            StreamReader sr = new StreamReader("../../../input.txt");
            var line = sr.ReadLine();
            int finalSum = 0;
            while (line != null)
            {
                line = line.Substring(line.IndexOf(": ") + 2);
                var sets = line.Split(";");
                List<Set> gameSets = new List<Set>();
                foreach (var setString in sets)
                {
                    var set = new Set(setString);
                    gameSets.Add(set);
                }
                gamesMinimums.Add(getSetOfMaxValues(gameSets));
                line = sr.ReadLine();
            }
            foreach (Set set in gamesMinimums)
            {
                finalSum += set.getPowerOfSet();
            }
            Console.WriteLine(finalSum);
        }

        private Set getSetOfMaxValues(List<Set> sets)
        {
            Set result = new Set();
            foreach(Set s in sets)
            {
                result.red = Math.Max(result.red, s.red);
                result.green = Math.Max(result.green, s.green);
                result.blue = Math.Max(result.blue, s.blue);
            }
            return result;
        }
    }

    internal class Set
    {
        public int red { get; set; }
        public int green { get; set; }
        public int blue { get; set; }

        public Set()
        {
            red = 0;
            green = 0;
            blue = 0;
        }

        public Set(String set)
        {
            this.red = 0;
            this.green = 0;
            this.blue = 0;

            var colours = set.Split(',');
            foreach ( var colour in colours)
            {
                var x = colour.Trim().Split(' ');
                switch (x[1].Trim()) 
                {
                    case "red":
                        this.red = int.Parse(x[0]);
                        break;
                    case "green":
                        this.green = int.Parse(x[0]); 
                        break;
                    case "blue":
                        this.blue = int.Parse(x[0]);
                        break;
                }
            }
        }

        public int getPowerOfSet()
        {
            return red * green * blue;
        }

        public bool test()
        {
            return red <= MaxValues.MAX_RED & green <= MaxValues.MAX_GREEN & blue <= MaxValues.MAX_BLUE;
        }
    }

    internal static class MaxValues
    {
        public const int MAX_RED = 12;
        public const int MAX_GREEN = 13;
        public const int MAX_BLUE = 14;
    }
}
