#include <iostream>

using namespace std;

class Money
{
    int cents;
    int banknote;

    void normalize()
    {
        while (cents >= 100)
        {
            banknote++;
            cents -= 100;
        }
        while (cents < 0)
        {
            banknote--;
            cents += 100;
        }

        if (banknote < 0)
        {
            banknote = 0;
            cents = 0;
        }
    }

public:
    int getCents() const { return cents; }
    int getBanknote() const { return banknote; }

    void setCents(int newCents)
    {
        cents = newCents;
        normalize();
    }
    void setBanknote(int newBanknote)
    {
        banknote = newBanknote;
    }

    Money() : cents(0), banknote(0) {}
    Money(int banknote, int cents)
    {
        setBanknote(banknote);
        setCents(cents);
    }

    Money& operator=(const Money& other)
    {
        setBanknote(other.getBanknote());
        setCents(other.getCents());
        return *this;
    }

    bool operator==(const Money& other) const
    {
        return banknote == other.banknote && cents == other.cents;
    }

    bool operator!=(const Money& other) const
    {
        return !(*this == other);
    }

    bool operator>(const Money& other) const
    {
        if (banknote != other.banknote) return banknote > other.banknote;
        return cents > other.cents;
    }

    bool operator<(const Money& other) const
    {
        return other > *this;
    }

    bool operator>=(const Money& other) const
    {
        return !(*this < other);
    }

    bool operator<=(const Money& other) const
    {
        return !(*this > other);
    }


    Money operator+(const Money& other) const
    {
        return Money(banknote + other.banknote, cents + other.cents);
    }

    Money& operator+=(const Money& other)
    {
        banknote += other.banknote;
        cents += other.cents;
        normalize();
        return *this;
    }

    Money operator-(const Money& other) const
    {
        return Money(banknote - other.banknote, cents - other.cents);
    }

    Money& operator-=(const Money& other)
    {
        banknote -= other.banknote;
        cents -= other.cents;
        normalize();
        return *this;
    }

    Money operator*(int val) const
    {
        Money result;
        result.banknote = banknote * val;
        result.cents = cents * val;

        result.normalize();

        return result;
    }

    Money& operator*=(int val)
    {
        banknote *= val;
        cents *= val;
        normalize();
        return *this;
    }

    Money operator/(int val) const
    {
        Money result;
        
        if (val == 0) return result;

        int TotalCents = banknote * 100 + cents;

        int total = TotalCents / val;
        result.banknote = total / 100;
        result.cents = total % 100;

        return result;
    }

    Money& operator/=(int val)
    {
        *this = *this / val;
        return *this;
    }


    Money& operator++()
    {
        cents++;
        normalize();
        return *this;
    }

    Money operator++(int)
    {
        Money temp = *this;
        ++(*this);
        return temp;
    }

    Money& operator--()
    {
        cents--;
        normalize();
        return *this;
    }

    Money operator--(int)
    {
        Money temp = *this;
        --(*this);
        return temp;
    }
};

static ostream& operator<<(ostream& os, const Money& m)
{
    if (m.getCents() < 10)
    {
        return os << m.getBanknote() << ".0" << m.getCents();
    }
    return os << m.getBanknote() << '.' << m.getCents();
}
static istream& operator>>(istream& is, Money& m)
{
    int banknote, cents;
    char dot;

    is >> banknote >> dot >> cents;

    if (dot == '.')
    {
        m.setBanknote(banknote);
        m.setCents(cents);
    }

    return is;
}


int main()
{




	return 0;
}