using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AoC_Day4
{
    internal class Task2
    {
        private class Card
        {
            public Card(int id, List<int> myNumbers, List<int> winningNunmbers)
            {
                this.id = id;
                this.myNumbers = myNumbers;
                this.winningNunmbers = winningNunmbers;
                this.copyCount = 1;
            }

            public int id { get; set; }
            public int copyCount { get; set; }
            public List<int> myNumbers { get; set; }
            public List<int> winningNunmbers { get; set; }
        }

        public void execute()
        {
            StreamReader sr = new StreamReader("../../../input.txt");
            var line = sr.ReadLine();
            List<Card> cards = new List<Card>();
            while (line != null)
            {
                var number = Int32.Parse(line.Substring(0, line.IndexOf(":")).Substring(4).Trim());
                line = line.Substring(line.IndexOf(": ") + 2);
                String[] halfs = line.Split("|");
                var myNumbers = halfs[0].Split().Where(n => !String.IsNullOrEmpty(n)).Select(x => Int32.Parse(x)).ToList();
                var winningNumbers = halfs[1].Split().Where(n => !String.IsNullOrEmpty(n)).Select(x => Int32.Parse(x)).ToList();
                cards.Add(new Card(number, myNumbers, winningNumbers));
                line = sr.ReadLine();
            }
            using(var enumerator = cards.GetEnumerator())
            {
                while (enumerator.MoveNext())
                {
                    var card = enumerator.Current;
                    int numberOfWinningNumbers = 0;
                    foreach (int i in card.myNumbers)
                    {
                        if (card.winningNunmbers.Contains(i))
                        {
                            numberOfWinningNumbers++;
                        }
                    }
                    Console.WriteLine(card.copyCount);
                    makeCopies(enumerator, numberOfWinningNumbers);
                }
            }
            Console.WriteLine("Sum of all cards: " + cards.Sum(x => x.copyCount).ToString());
        }

        private void makeCopies(List<Card>.Enumerator cardEnumerator, int numberOfWinningNumbers)
        {
            var winnerCopyCount = cardEnumerator.Current.copyCount;
            while(cardEnumerator.MoveNext() && numberOfWinningNumbers > 0) 
            { 
                cardEnumerator.Current.copyCount = cardEnumerator.Current.copyCount + winnerCopyCount;
                numberOfWinningNumbers--;
            }
        }
    }
}
