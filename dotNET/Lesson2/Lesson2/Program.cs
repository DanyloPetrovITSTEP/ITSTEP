/*using System.Text;

namespace Lesson2
{
    internal class Program
    {
        class Person
        {
            string Name;
            int Age;
        }

        static void Main(string[] args)
        {
            int[] arr_1 = new int[10];
            int[] arr_2 = { 1, 2, 3, 4, 5 };

            Person[] persons_arr = new Person[3];

            Console.WriteLine(arr_1.Length); // 10
            Console.WriteLine(arr_2.Length); // 5


            Console.WriteLine(arr_2[0]); // 1
            Console.WriteLine(arr_2[1]); // 2
            //Console.WriteLine(arr_2[5]); // Error: out of range

            foreach (int i in arr_2)
            {
                Console.WriteLine(i);
            }


            int[,] marr_1 = new int[2, 3]; // [int 0 0] [int 0 1] [int 0 2] [int 1 0] [int 1 1] [int 1 2]
            int[][] marr_2 = new int[2][]; // [ref 0] [ref 1]

            marr_2[0] = new int[5]; // [int 0] [int 1] [int 2] [int 3] [int 4]
            marr_2[1] = new int[15]; // [int 0] [int 1] [int 2] .... [int 14]
            
            ////////////////////////////////////////////////////
            
            int? i_1 = null;
            int? i_2 = 123;

            Console.WriteLine(i_1); //
            Console.WriteLine(i_2); // 123

            Console.WriteLine(i_1 ?? 0); // 0

            int[]? arr_null = null;
            Console.WriteLine(arr_null?.Length ?? 0); // 0


            arr_null ??= new int[10];
            Console.WriteLine(arr_null?.Length ?? 0); // 10

            string? input = null;
            // input == ....

            *//*if (input == null)
            {
                name = "Unknown";
            }
            else
            {
                name = input;
            }*//*

            string name = input ?? "Unknown";

            /////////////////////////////////////////////////

            string text = "Hello";

            string b = text;

            b += text;


            string result = "";

            for (int i = 0; i < 100; i++)
            {
                result += i;
            }
            // ""
            // "0"
            // "01"
            // "012"
            // "0123"
            // "01234"
            // "012345"

            StringBuilder builder = new StringBuilder(); // ""

            for (int i = 0; i < 100; i++)
            {
                builder.Append(i);
            }
            // "012345"

            string str = builder.ToString();

            Console.WriteLine("A".Length); // 1
            Console.WriteLine("👋".Length); // 2

            string str_res = str.ToUpper();

            int res = 123;

            string text_2 = $"Result: {{{res}}}"; // Result: {123}
        }
    }
}*/