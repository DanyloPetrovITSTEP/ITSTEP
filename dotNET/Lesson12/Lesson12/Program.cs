/*using FileStream stream  = new FileStream("data.bin", FileMode.Create, FileAccess.Write);

byte[] data = [10, 20, 30, 40];

stream.Write(data);*/
//\bin\Debug\net10.0

/*try
{
    using (FileStream stream = File.OpenRead("data.bin"))
    {
        byte[] buffer = new byte[stream.Length];
    
        stream.ReadExactly(buffer);
    
        Console.WriteLine(string.Join(", ", buffer));
    }
}
catch(Exception e)
{
    Console.WriteLine(e.Message);
}*/

/*StreamWriter writer = new("test_data.txt");
writer.WriteLine("Hello World! 1");
writer.WriteLine("Hello World! 2");
writer.WriteLine("Hello World! 3");
writer.Dispose();

StreamReader reader = new("test_data.txt");
while (!reader.EndOfStream)
{
    Console.WriteLine(reader.ReadLine());
}
reader.Dispose();*/

/*BinaryWriter writer = new (File.Open("bdata.bin", FileMode.Create));
writer.Write(100);
writer.Write(100.1231f);
writer.Write("100.1231f");
writer.Dispose();

BinaryReader reader = new (File.OpenRead("bdata.bin"));
int intData = reader.ReadInt32();
float floatData = reader.ReadSingle();
string stringData = reader.ReadString();*/

/*FileInfo info = new FileInfo("bdata.bin");
Console.Write(info.Directory.FullName);*/

/*
Console.WriteLine(File.ReadAllText("test_data.txt"));*/

