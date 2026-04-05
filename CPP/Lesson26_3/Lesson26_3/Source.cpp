#include <iostream>
using namespace std;

class Timer
{
	int timeInSeconds;

public:

	explicit Timer(int sec)
	{
		timeInSeconds = sec;
	}

	explicit Timer(double minutes)
	{
		timeInSeconds = minutes * 60;
	}

	explicit Timer(float hours)
	{
		timeInSeconds = hours * 3600;
	}

	int GetSeconds() const // Повернути час у секундах
	{
		return timeInSeconds;
	}

	int GetMinutes() const // Повернути час у хвилинах (ціле)
	{
		return (timeInSeconds / 60);
	}

	int GetHours() const // Повернути час у годинах (ціле)
	{
		return (timeInSeconds / 3600);
	}

	void Print() const // Висновок у форматі "X годин, Y хвилин, Z секунд"
	{
		int hours = timeInSeconds / 3600;
		int minutes = (timeInSeconds % 3600) / 60;
		int seconds = timeInSeconds % 60;

		cout << hours << " hours, " << minutes << " minutes, " << seconds << " seconds" << endl;
	}
};


int main()
{
	Timer sec(120);
	Timer min(3.5);
	Timer hours(2.5f); // якщо я не помиляюсь, то f в кінці числа каже компілятору що це флоат, а не дабл

	sec.Print();
	cout << "---------------" << endl;
	min.Print();
	cout << "---------------" << endl;
	hours.Print();
}