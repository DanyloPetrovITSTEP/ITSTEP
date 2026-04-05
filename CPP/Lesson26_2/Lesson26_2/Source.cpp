#include <iostream>
#include <ctime>
using namespace std;

class BankAccount
{
	float balance = 0;
	int accountNumber;
	static int lastAccountNumber;
	static int accountsCount;
	mutable time_t lastAccessTime = time(nullptr);
	
public:

	BankAccount()
	{
		accountsCount++;
		accountNumber = ++lastAccountNumber;
		cout << "Account created!" << endl;
	}

	float GetBalance() const
	{
		lastAccessTime = time(nullptr);
		return balance;
	}

	void AddMoneyToBal(float money)
	{
		lastAccessTime = time(nullptr);
		balance += money;
	}

	void TakeMoneyFromBal(float money)
	{
		lastAccessTime = time(nullptr);
		balance -= money;
	}

	int GetAccountNumber() const
	{
		return accountNumber;
	}

	static int GetAccountsCount()
	{
		return accountsCount;
	}

	time_t GetLastAccessTime() const // Тестова функція
	{
		return lastAccessTime;
	}

	~BankAccount()
	{
		accountsCount--;
	}
};

int BankAccount::accountsCount = 0;
int BankAccount::lastAccountNumber = 0;

int main()
{
	BankAccount acc1;
	BankAccount acc2;
	cout << BankAccount::GetAccountsCount() << endl;
	cout << "acc1 ID: " << acc1.GetAccountNumber() << endl;
	cout << "acc2 ID: " << acc2.GetAccountNumber() << endl;

	{
		BankAccount acc3;
		cout << "acc3 ID: " << acc3.GetAccountNumber() << endl;
		cout << BankAccount::GetAccountsCount() << endl;
	}

	cout << BankAccount::GetAccountsCount() << endl;
	BankAccount acc4;
	cout << "acc4 ID: " << acc4.GetAccountNumber() << endl;
	cout << BankAccount::GetAccountsCount() << endl;
	

	return 0;
}