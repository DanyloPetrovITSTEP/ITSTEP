#include <iostream>
using namespace std;

class Stopwatch {
	int seconds;                		// Поточний час у секундах
	bool paused;                		// Чи на паузі
	mutable int queryCount;     	    // Кількість викликів GetSeconds/GetMinutes

	static int stopwatchCount;          // Загальна кількість створених секундомірів
	static int activeStopwatches;   			// Кількість секундомірів, що зараз "тікають"

	time_t lastTick = time(nullptr);

public:
	explicit Stopwatch(int sec) : seconds(sec), paused(false), queryCount(0)         // Ініціалізація секундами
	{
		lastTick = time(nullptr);
		stopwatchCount++;
		activeStopwatches++;
	}

	explicit Stopwatch(double min) : seconds(min * 60), paused(false), queryCount(0)    			// Ініціалізація хвилинами
	{
		lastTick = time(nullptr);
		stopwatchCount++;
		activeStopwatches++;
	}

	~Stopwatch()
	{
		if (!paused)
		{
			activeStopwatches--;
		}
	}

	void Tick()                   			   // Оновлюе значення seconds залежно вiд значення що повертае std::time(nullptr), якщо не на паузі
	{
		if (!paused)
		{
			time_t currentTime = time(nullptr);
			seconds += (currentTime - lastTick);
			lastTick = currentTime;
		}
	}

	void pause(bool pauseState = true)         // Ставит секундомір на паузу або знімає паузу
	{
		if (pauseState && !paused)
		{
			paused = true;
			activeStopwatches--;
		}
		else if (!pauseState && paused)
		{
			paused = false;
			lastTick = time(nullptr);
			activeStopwatches++;
		}
	}

	int GetSeconds() const
	{
		queryCount++;
		return seconds;
	}

	double GetMinutes() const
	{
		queryCount++;
		return (seconds / 60.0);
	}

	static int GetStopwatchCount()
	{
		return stopwatchCount;
	}

	static int GetActStopwatchCount()
	{
		return activeStopwatches;
	}

	int GetQueryCount() const
	{
		return queryCount;
	}
};

int Stopwatch::stopwatchCount = 0;
int Stopwatch::activeStopwatches = 0;



int main()
{
	Stopwatch first(60);
	Stopwatch second(1.5);

	first.Tick();
	cout << first.GetSeconds() << endl;
	cout << first.GetMinutes() << endl;

	first.pause();

	cout << "--------------------" << endl;

	second.Tick();

	cout << "Active stopwatches count: " << Stopwatch::GetActStopwatchCount() << endl;
	cout << "All stopwatches count: " << Stopwatch::GetStopwatchCount() << endl;

	return 0;
}