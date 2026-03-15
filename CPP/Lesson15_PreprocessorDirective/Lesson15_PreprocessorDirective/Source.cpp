#include <iostream>
using namespace std;

#define def int
#define Main main()
#define begin {
#define end }
#define print cout <<
#define input cin >>
#define array int
#define var int // variable, хоч якось замінити int
#define for_in_range(i,n) for (int i = 0; i < n; i++)
#define repeat(k) for (int j = 0; j < k; j++)
#define if_(cond) if(cond){
#define elif(cond) } else if(cond){
#define else_ } else {

def Main begin

    var n;

    print "Введіть розмір масиву: ";
    input n;

    if_(n <= 0)
        print "Розмір масиву має бути більше 0! \n";
        return 0;
    }

    array arr[100];

    print "Введіть елементи масиву: \n";
        for_in_range(i, n) begin
            input arr[i];
    end

    var k;
    char direction;

    print "Введіть кількість кроків зсуву: ";
    input k;
    print "Введіть напрям (L - вліво, R - вправо): ";
    input direction;

    k = k % n;

    if_(direction == 'L' || direction == 'l') begin
        repeat(k) begin
            var first = arr[0];
            for (int i = 0; i < n - 1; i++) begin
                arr[i] = arr[i + 1];
            end
            arr[n - 1] = first;
        end
    end

    elif(direction == 'R' || direction == 'r') begin
        repeat(k) begin
            var last = arr[n - 1];
            for (int i = n - 1; i > 0; i--) begin
                arr[i] = arr[i - 1];
            end
        arr[0] = last;
        end
    end

    else_ begin
        print "Неправильний напрям!";
        return 0;
    end

    print "Оновлений масив: \n";
    for_in_range(i, n) begin
        print arr[i] << " ";
    end

    return 0;
end