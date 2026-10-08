using Lesson7;
/*Створіть консольну програму з різними видами транспорту. Створіть інтерфейс IMovable, який містить метод void Move() та властивість int Speed { get; }.
Створіть три класи: Car, Bicycle, Boat. Кожен клас повинен реалізовувати IMovable, мати власну швидкість та власну реалізацію методу Move().
Створіть List<IMovable>, додайте до нього об'єкти різних типів та за допомогою foreach викличте Move() для кожного об'єкта.
Реалізуйте IComparable<T> для одного з класів або для спільного типу транспорту. Порівнювати об'єкти потрібно за швидкістю.
Створіть окремий клас, який реалізує IComparer<IMovable> та сортує транспорт за назвою класу.
Створіть клас TransportPark, який зберігає список транспорту та реалізує IEnumerable<IMovable>, щоб об'єкти парку можна було перебирати напряму через foreach.*/


List<IMovable> transportList = new List<IMovable>
{
    new Car(120),
    new Bicycle(25),
    new Boat(40)
};

Console.WriteLine("Перелік транспортних засобів:");
foreach (var transport in transportList)
{
    transport.Move();
}


transportList.Sort((a, b) => a.Speed.CompareTo(b.Speed));
Console.WriteLine("\nСортування за швидкістю:");
foreach (var t in transportList)
{
    Console.WriteLine($"{t.GetType().Name}: {t.Speed} км/год");
}


transportList.Sort(new SortByName());
Console.WriteLine("\nСортування за назвою класу:");
foreach (var t in transportList)
{
    Console.WriteLine($"{t.GetType().Name}: {t.Speed} км/год");
}


var park = new TransportPark();
park.AddTransport(new Car(90));
park.AddTransport(new Bicycle(15));
park.AddTransport(new Boat(30));
Console.WriteLine("\nПерелік транспорту :");
foreach (var t in park)
{
    Console.WriteLine($"{t.GetType().Name}: {t.Speed} км/год");
}


var cars = new List<Car> { new Car(120), new Car(90), new Car(150) };
cars.Sort();
Console.WriteLine("\nМашини відсортовані за швидкістю:");
for (int i = 0; i < cars.Count; i++)
{
    Console.WriteLine($"Машина_{i + 1}: {cars[i].Speed} км/год");
}