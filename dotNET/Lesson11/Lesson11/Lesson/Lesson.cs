/*// LINQ - Language Integrated Query 

List<int> nums = new List<int> { -2, 1, 4, 7, 9, 10 };

List<int> result = new();

foreach (var num in nums)
{
    if (num % 2 == 0)
    {
        result.Add(num);
    }
}

result = nums.Where(num => num % 2 == 0).ToList();

//result = (List<int>)from num in nums where num % 2 == 0 select num;

var query = nums
    .Where(num => num % 2 == 0);
//.Sum(num => num);

foreach (var num in query)
{
    Console.Write($"{num} ");
}
Console.WriteLine();

nums.Add(12);

foreach (var num in query)
{
    Console.Write($"{num} ");
}

// Deferred execution
// 1. Where
// 2. Select
// 3. OrderBy
// 4. GroupBy
// 5. Take

// Immediate execution
// 1. ToList
// 2. Sum
// 3. Count
// 4. ToArray
// 5. First



List<Product> products =
[
    new Product(1, "Keyboard", "Electronics", 80, 10, new[] { "PC", "Input" }),
    new Product(2, "Mouse", "Electronics", 40, 0, new[] { "PC", "Input" }),
    new Product(3, "Monitor", "Electronics", 250, 3, new[] { "PC", "Display" }),
    new Product(4, "C# Book", "Books", 30, 8, new[] { "Education" }),
    new Product(5, "UE Book", "Books", 60, 4, new[] { "Education", "UE" }),
    new Product(6, "Gamepad", "Electronics", 60, 5, new[] { "PC", "Gaming", "Input" }),
    new Product(7, "CCCC", "Stationery", 10, 0, new[] { "Education" })
];

const int pageSize = 3;
int page = 1;

var query = products
    //.Where(n => n.Category == "Electronics")
    .OrderBy(n => n.Name[0])
    .ThenByDescending(n => n.Price)
    .Skip((page - 1) * pageSize)
    .Take(pageSize);

foreach (var product in query.Select(n => $"{n.Id} - {n.Name} | {n.Price}"))
{
    Console.WriteLine(product);
}

Console.WriteLine($"Count: {query.Count()}");
Console.WriteLine($"Price Sum: {query.Sum(n => n.Price)}");
Console.WriteLine($"Price Average: {query.Average(n => n.Price)}");
Console.WriteLine($"First: {query.FirstOrDefault()}");
Console.WriteLine($"Any PC: {query.Any(n => n.Tags.Any(s => s == "PC"))}");
Console.WriteLine($"All PC: {query.All(n => n.Tags.Any(s => s == "PC"))}");

List<Product> list = query.ToList();
Product[] array = query.ToArray();

var groups = products
    .GroupBy(n => n.Category);

Console.WriteLine();
foreach (var group in groups)
{
    Console.WriteLine(group.Key);

    foreach (var product in group)
    {
        Console.WriteLine(product);
    }
}

var query_2 = products
    .GroupBy(n => n.Category)
    .Select(g => new
    {
        Category = g.Key,
        Count = g.Count(),
        Sum = g.Sum(n => n.Price),
        Average = g.Average(n => n.Price),
    })
    .OrderBy(n => n.Average);

foreach (var group in query_2)
{
    Console.WriteLine(group);
}

var tags = products
    .SelectMany(n => n.Tags)
    .Distinct();

foreach (var tag in tags)
{
    Console.WriteLine(tag);
}

products.SingleOrDefault(p => p.Id == 1);

/////

List<Order> orders = new()
{
    new(1, 1, 3),
    new(2, 1, 2),
    new(3, 3, 1),
    new(4, 4, 2),
};

var result = orders.Join(
    products,
    order => order.ProductId,
    product => product.Id,
    (o, p) => new
    {
        ProductName = p.Name,
        o.Quantity,
        TotalPrice = p.Price * o.Quantity,
    }
);

foreach (var order in result)
{
    Console.WriteLine(order);
}*/