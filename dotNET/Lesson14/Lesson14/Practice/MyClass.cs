using System;
using System.Collections.Generic;
using System.Text;

namespace Lesson14.Practice
{
    public class Vector3D
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public Vector3D() { }

        public Vector3D(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public override string ToString()
        {
            return $"({X}, {Y}, {Z})";
        }
    }

    public class CargoItem
    {
        public string Name { get; set; } = "";
        public int Quantity { get; set; }
        public float Weight { get; set; }

        public CargoItem() { }

        public CargoItem(string name, int quantity, float weight)
        {
            Name = name;
            Quantity = quantity;
            Weight = weight;
        }

        public override string ToString()
        {
            return $"{Name}: {Quantity} pcs, {Weight} kg each";
        }
    }

    public class Spaceship
    {
        public string Name { get; set; } = "";
        public int Health { get; set; }
        public float Fuel { get; set; }
        public Vector3D Position { get; set; } = new Vector3D();
        public List<CargoItem> Cargo { get; set; } = new List<CargoItem>();

        public bool IsEngineRunning { get; set; }
        public float DistanceTraveled { get; set; }
        public string LastCommand { get; set; } = "";

        public void StartEngine()
        {
            if (Fuel > 0)
            {
                IsEngineRunning = true;
                LastCommand = "Engine started";
            }
            else
            {
                LastCommand = "Not enough fuel";
            }
        }

        public void StopEngine()
        {
            IsEngineRunning = false;
            LastCommand = "Engine stopped";
        }

        public void Move(float x, float y, float z)
        {
            if (!IsEngineRunning)
            {
                LastCommand = "Engine is not running";
                return;
            }

            float distance = MathF.Sqrt(x * x + y * y + z * z);

            float fuelCost = distance * 0.1f;

            if (Fuel < fuelCost)
            {
                LastCommand = "Not enough fuel to move";
                return;
            }

            Fuel -= fuelCost;

            Position.X += x;
            Position.Y += y;
            Position.Z += z;

            DistanceTraveled += distance;

            LastCommand = "Ship moved";
        }

        public void TakeDamage(int damage)
        {
            if (damage <= 0)
                return;

            Health = Math.Max(0, Health - damage);
            LastCommand = $"Ship took {damage} damage";
        }

        public void AddCargo(CargoItem item)
        {
            Cargo.Add(item);
            LastCommand = $"Cargo added: {item.Name}";
        }

        public float GetTotalCargoWeight()
        {
            float totalWeight = 0;

            foreach (CargoItem item in Cargo)
            {
                totalWeight += item.Quantity * item.Weight;
            }

            return totalWeight;
        }

        public override string ToString()
        {
            string result = $"Name: {Name}\n" +
                            $"Health: {Health}\n" +
                            $"Fuel: {Fuel:F2}\n" +
                            $"Position: {Position}\n" +
                            $"Engine running: {IsEngineRunning}\n" +
                            $"Distance traveled: {DistanceTraveled:F2}\n" +
                            $"Last command: {LastCommand}\n" +
                            $"Total cargo weight: {GetTotalCargoWeight():F2} kg\n" +
                            "Cargo:\n";

            foreach (CargoItem item in Cargo)
            {
                result += $"  - {item}\n";
            }

            return result;
        }
    }

    public class SpaceshipJsonDto
    {
        public string Name { get; set; } = "";
        public int Health { get; set; }
        public float Fuel { get; set; }
        public Vector3D Position { get; set; } = new Vector3D();
        public List<CargoItem> Cargo { get; set; } = new List<CargoItem>();

        public SpaceshipJsonDto() { }

        public SpaceshipJsonDto(Spaceship spaceship)
        {
            Name = spaceship.Name;
            Health = spaceship.Health;
            Fuel = spaceship.Fuel;

            Position = new Vector3D(
                spaceship.Position.X,
                spaceship.Position.Y,
                spaceship.Position.Z
            );

            Cargo = new List<CargoItem>();

            foreach (CargoItem item in spaceship.Cargo)
            {
                Cargo.Add(new CargoItem(
                    item.Name,
                    item.Quantity,
                    item.Weight
                ));
            }
        }

        public Spaceship Load()
        {
            Spaceship spaceship = new Spaceship()
            {
                Name = Name,
                Health = Health,
                Fuel = Fuel,
                Position = new Vector3D(
                    Position.X,
                    Position.Y,
                    Position.Z
                ),
                IsEngineRunning = false,
                DistanceTraveled = 0,
                LastCommand = ""
            };

            foreach (CargoItem item in Cargo)
            {
                spaceship.Cargo.Add(new CargoItem(
                    item.Name,
                    item.Quantity,
                    item.Weight
                ));
            }

            return spaceship;
        }
    }
}
