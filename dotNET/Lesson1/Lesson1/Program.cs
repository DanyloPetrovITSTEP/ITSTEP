namespace Lesson1
{
    internal class Program
    {
        enum AgeState
        {
            None,
            Adult,
            Young
        }

        static void Main(string[] args)
        {
            /*// + - * / %
            // == != < > <= >=
            // && || !
            // & | << >> ~
            // = += -= *= /= ??=


            // A && B /\ A || B
            // A() && B()

            int age = 10;

            if (age >= 10)
            {

            }
            else if (age <= 65)
            {

            }
            else
            {

            }


            AgeState age_state = age >= 18 ? AgeState.Adult : AgeState.Young;


            switch (age_state)
            {
                case AgeState.Adult: *//*Test_1()*//* break;
                case AgeState.Young: *//*Test_2()*//* break;
                default: *//*Test_3()*//* break;
            }


            string age_string_state = age_state switch
            {
                AgeState.Adult => "Adult",
                AgeState.Young => "Young",
            };


            age_state = age switch
            {
                <= 0 => AgeState.None,
                < 18 => AgeState.Young,
                _ => AgeState.Adult,
            };



            for(int i = 0; i < 10 ; i++)
            {
                
            }


            while (true)
            {
                break;
            }


            do
            {

            } while (true);*/



            int Test = 0;

            Console.WriteLine(nameof(Test));
        }
    }
}