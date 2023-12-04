using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AoC_Day4
{
    internal class Task1
    {
        public static void execute()
        {
            StreamReader sr = new StreamReader("../../../input.txt");
            var line = sr.ReadLine();
            List<int> myNumbers = new List<int>();
            List<int> winningNumbers = new List<int>();
            int sum = 0;
            while (line != null)
            {
                line = line.Substring(line.IndexOf(": ") + 2);
                String[] halfs = line.Split("|");
                myNumbers = halfs[0].Split().Where(n => !String.IsNullOrEmpty(n)).Select(x => Int32.Parse(x)).ToList();
                winningNumbers = halfs[1].Split().Where(n => !String.IsNullOrEmpty(n)).Select(x => Int32.Parse(x)).ToList();
                int partialSum = 0;
                foreach (int i in myNumbers)
                {
                    if (winningNumbers.Contains(i))
                    {
                        partialSum = (partialSum == 0) ? 1 : partialSum * 2;
                    }
                }
                Console.WriteLine(partialSum);
                sum += partialSum;
                line = sr.ReadLine();
            }
            Console.WriteLine(sum);
        }
    }
}
