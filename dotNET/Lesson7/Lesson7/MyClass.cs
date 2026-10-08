using System;
using System.Collections.Generic;
using System.Text;

/*Створіть консольну програму з різними видами транспорту. Створіть інтерфейс IMovable, який містить метод void Move() та властивість int Speed { get; }.
Створіть три класи: Car, Bicycle, Boat. Кожен клас повинен реалізовувати IMovable, мати власну швидкість та власну реалізацію методу Move().
Створіть List<IMovable>, додайте до нього об'єкти різних типів та за допомогою foreach викличте Move() для кожного об'єкта.
Реалізуйте IComparable<T> для одного з класів або для спільного типу транспорту. Порівнювати об'єкти потрібно за швидкістю.
Створіть окремий клас, який реалізує IComparer<IMovable> та сортує транспорт за назвою класу.
Створіть клас TransportPark, який зберігає список транспорту та реалізує IEnumerable<IMovable>, щоб об'єкти парку можна було перебирати напряму через foreach.*/

namespace Lesson7
{
    interface IMovable
    {
        void Move();
        int Speed { get; }
    }

    class Car : IMovable, IComparable<Car>
    {
        public int Speed { get; private set; }
        public Car(int speed)
        {
            Speed = speed;
        }
        public void Move()
        {
            Console.WriteLine($"Машина рухається зі швидкістю {Speed} км/год.");
        }
        public int CompareTo(Car other)
        {
            if (other == null) return 1;
            return this.Speed.CompareTo(other.Speed);
        }
    }

    class Bicycle : IMovable
    {
        public int Speed { get; private set; }
        public Bicycle(int speed)
        {
            Speed = speed;
        }
        public void Move()
        {
            Console.WriteLine($"Велосипед рухається зі швидкістю {Speed} км/год.");
        }
    }

    class Boat : IMovable
    {
        public int Speed { get; private set; }
        public Boat(int speed)
        {
            Speed = speed;
        }
        public void Move()
        {
            Console.WriteLine($"Човен рухається зі швидкістю {Speed} км/год.");
        }
    }

    class SortByName : IComparer<IMovable>
    {
        public int Compare(IMovable x, IMovable y)
        {
            if (ReferenceEquals(x, y)) return 0;
            if (x == null) return -1;
            if (y == null) return 1;
            return string.Compare(x.GetType().Name, y.GetType().Name, StringComparison.Ordinal);
        }
    }

    class TransportPark : IEnumerable<IMovable>
    {
        private List<IMovable> transportList = new List<IMovable>();
        public void AddTransport(IMovable transport)
        {
            transportList.Add(transport);
        }
        public IEnumerator<IMovable> GetEnumerator()
        {
            return transportList.GetEnumerator();
        }
        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
    }
}
