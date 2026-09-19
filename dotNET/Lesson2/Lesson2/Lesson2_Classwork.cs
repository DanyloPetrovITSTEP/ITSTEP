using System;
using System.Collections.Generic;
using System.Text;

namespace Lesson2
{
    internal class Lesson2_Classwork
    {
        static void Main(string[] args)
        {
            /*// ex.1

            int[] arr = { -12, 5, -3, 14, 0, -8, 9, 2, -15, 11, -1, 7, 15, -6, 4, -10, 1, 13, -4, 8 };

            int min = arr[0], max = arr[0];
            int minIndex = 0, maxIndex = 0;
            double average = 0;

            for (int i = 0; i < arr.Length; i++)
            {
                int num = arr[i];
                if (num < min) { min = num; minIndex = i; }
                if (num > max) { max = num; maxIndex = i; }
                average += (double)num;
            }

            average = average / arr.Length;

            Console.WriteLine($"Min: {min}, index: {minIndex}");
            Console.WriteLine($"Max: {max}, index: {maxIndex}");
            Console.WriteLine($"Average: {average}");



            // ex.2



            int[,] field = new int[10, 10];

            for (int row = 0; row < 10; row++)
            {
                for (int col = 0; col < 10; col++)
                {
                    if (col % 2 == 0)
                    {
                        field[row, col] = 1;
                    }
                    else
                    {
                        field[row, col] = 0;
                    }
                }
            }

            for (int row = 0; row < 10; row++)
            {
                int countFreeCells = 0;

                for (int col = 0; col < 10; col++)
                {
                    if (field[row, col] == 0)
                    {
                        Console.Write("0");
                        countFreeCells++;
                    }
                    else
                    {
                        Console.Write("#");
                    }
                }

                Console.WriteLine($" | Count of free cells in this row: {countFreeCells}");
            }



            // ex.3



            string?[] players = { "Alex", null, "Kate", null, "John", null };

            int nullNames = 0;

            for (int i = 0; i < players.Length; i++)
            {
                if (players[i] == null)
                {
                    players[i] = $"Player_{i + 1}";
                    nullNames++;
                }
            }

            Console.WriteLine($"Count of names that are missing: {nullNames}");

            for (int i = 0; i < players.Length; i++)
            {
                Console.WriteLine(players[i]);
            }



            // ex.4



            string?[] messages =
            {
                "Program started",
                null,
                "Client connected",
                "Error",
                null,
                "Program finished"
            };

            for (int i = 0; i < messages.Length; i++)
            {
                if (messages[i] == null)
                {
                    messages[i] = "No message";
                }
            }
            for (int i = 0; i < messages.Length; i++)
            {
                Console.WriteLine(messages[i]);
            }



            // ex.5



            string text = " Unreal Engine Gameplay Programming ";

            StringBuilder builder = new StringBuilder();

            int wordCount = 0;
            string longestWord = "";
            string currentWord = "";

            bool isInWord = false;

            for (int i = 0; i < text.Length; i++)
            {
                char symbol = text[i];

                if (symbol != ' ')
                {
                    builder.Append(symbol);
                    currentWord += symbol;

                    if (!isInWord)
                    {
                        isInWord = true;
                        wordCount++;
                    }
                }
                else
                {
                    if (isInWord)
                    {
                        builder.Append(' ');

                        if (currentWord.Length > longestWord.Length)
                        {
                            longestWord = currentWord;
                        }

                        currentWord = "";
                        isInWord = false;
                    }
                }
            }

            if (currentWord.Length > longestWord.Length)
            {
                longestWord = currentWord;
            }

            string result = builder.ToString();

            Console.WriteLine($"Text: {result}");
            Console.WriteLine($"Word count: {wordCount}");
            Console.WriteLine($"Longest word: {longestWord}");



            // ex.6

            

            string code = "Player_17-HP_085-Weapon_Rifle";

            int firstUnderscore = code.IndexOf('_');
            int firstDash = code.IndexOf("-");

            string playerNumber = code.Substring(firstUnderscore + 1, firstDash - firstUnderscore - 1);


            int secondUnderscore = code.IndexOf("_", firstUnderscore + 1);
            int secondDash = code.IndexOf("-", firstDash + 1);


            int hp = 0;
            for (int i =  secondUnderscore + 1; i < secondDash; i++)
            {
                hp = hp * 10 + (code[i] - '0');
            }


            int thirdUnderscore = code.IndexOf("_", secondUnderscore + 1);

            string weapon = code.Substring(thirdUnderscore + 1);


            string result = $"Player #{playerNumber} has {hp} HP and uses {weapon}";

            Console.WriteLine(result);*/
        }
    }
}
