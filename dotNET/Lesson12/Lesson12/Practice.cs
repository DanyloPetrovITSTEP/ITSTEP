using System;
using System.Collections.Generic;
using System.Text;

while(true)
{
    PrintMenu();
    Console.Write("Enter your choice with number: ");
    string choice = Console.ReadLine();

    switch (choice)
    {
        case "1":
            {
                Console.Write("Enter file name: ");
                string file = Console.ReadLine();

                StreamWriter writer = new($"{file}.txt");
                writer.Dispose();

                Console.WriteLine("File created.");

                break;
            }

        case "2":
            {
                Console.Write("Enter file name: ");
                string file = Console.ReadLine();

                Console.Write("Enter text: ");
                string text = Console.ReadLine();

                using (StreamWriter writer = new StreamWriter($"{file}.txt", true))
                {
                    writer.WriteLine(text);
                }

                Console.WriteLine("Text saved in file.");
                break;
            }

        case "3":
            {
                Console.Write("Enter file name: ");
                string file = Console.ReadLine();

                Console.WriteLine("Reading file:");
                using (StreamReader reader = new StreamReader($"{file}.txt"))
                {
                    while (!reader.EndOfStream)
                    {
                        Console.WriteLine(reader.ReadLine());
                    }
                }

                break;
            }

        case "4":
            {
                Console.Write("Enter file name: ");
                string fromFile = Console.ReadLine();

                Console.Write("Enter copy name: ");
                string toFile = Console.ReadLine();

                using (FileStream input = File.OpenRead($"{fromFile}.txt"))
                using (FileStream output = new FileStream($"{toFile}.txt", FileMode.Create, FileAccess.Write))
                {
                    byte[] buffer = new byte[input.Length];

                    input.ReadExactly(buffer);
                    output.Write(buffer);
                }

                Console.WriteLine("File copied.");
                break;
            }

        case "5":
            {
                Console.WriteLine("Reading directory: ");

                string[] files = Directory.GetFiles(".");

                foreach (string file in files)
                {
                    Console.WriteLine(Path.GetFileName(file));
                }

                break;
            }

        case "6":
            {
                Console.Write("Enter file name: ");
                string file = Console.ReadLine();

                FileInfo info = new FileInfo($"{file}.txt");

                Console.WriteLine("Name: " + info.Name);
                Console.WriteLine("Path: " + info.FullName);
                Console.WriteLine("Size: " + info.Length + " bytes");
                Console.WriteLine("Date: " + info.CreationTime);
                Console.WriteLine("Type: " + info.Extension);

                break;
            }

        case "7":
            {
                Console.Write("Enter name: ");
                string name = Console.ReadLine();

                Console.Write("Enter age: ");
                int age = int.Parse(Console.ReadLine());

                Console.Write("Enter e-mail address: ");
                string email = Console.ReadLine();

                using (FileStream stream = new FileStream("user_data.bin", FileMode.Create, FileAccess.Write))
                using (BinaryWriter writer = new BinaryWriter(stream))
                {
                    writer.Write(name);
                    writer.Write(age);
                    writer.Write(email);
                }

                Console.WriteLine("User data saved.");
                break;
            }

        case "8":
            {
                using (FileStream stream = File.OpenRead("user_data.bin"))
                using (BinaryReader reader = new BinaryReader(stream))
                {
                    string name = reader.ReadString();
                    int age = reader.ReadInt32();
                    string email = reader.ReadString();

                    Console.WriteLine("Name: " + name);
                    Console.WriteLine("Age: " + age);
                    Console.WriteLine("E-mail address: " + email);
                }

                break;
            }

        case "9":
            {
                Console.Write("Enter file name WITH FILE.TYPE: ");
                string path = Console.ReadLine();

                File.Delete(path);

                Console.WriteLine("File deleted.");
                break;
            }

        case "0":
            return;

        default:
            Console.WriteLine("Error! Invalid choice number. Should be from 1 to 9");
            break;
    }
}













void PrintMenu()
{
    Console.WriteLine("===== FILE MANAGER =====");
    Console.WriteLine("1. Create .txt file");
    Console.WriteLine("2. Save text to file");
    Console.WriteLine("3. Read .txt file");
    Console.WriteLine("4. Copy file");
    Console.WriteLine("5. Read list of files");
    Console.WriteLine("6. Read file information");
    Console.WriteLine("7. Save user data to file");
    Console.WriteLine("8. Read user data");
    Console.WriteLine("9. Delete file");
    Console.WriteLine("0. Exit");
}