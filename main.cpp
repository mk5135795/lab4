#include <stdio.h>
#include <string>

using namespace std;

const char *print_num(int v);
char *dig(int n);
int k(int n);
int k_manual(int n);
int k_manual_old(int n);
int pow(int a, int b);//nie bylem zadowolony z dzialania pow() z math.h

int main(int argc, char *argv[])
{
    if(argc > 1)
        printf("k = %s\n", print_num( k( atoi( argv[1] ) ) ) );
    /*
    niby powinienem cos zmienic, dodac if(), bo k() ma zakres 0 - 2147483647 (ujemna sa obcinane), a print_num() 0 - 1'000'000
    i wyswietla "zero" lub "poza zakresem", gdy wynik jest poza zakresem print_num(),
    ale z drugiej strony jest to jakas informacja ze wynik da sie wyswietlic ale nie za pomoca funkcji print_num()
    */
    return 0;
}

const char *print_num(int v){
    string str = to_string(v), tmp;
    if(v < 0)
        v *= -1;
    if(v == 0)
        return " zero";
    if(v == 1000000)
        return " milion";
    if(v > 1000000)
        return " poza zakresem (ponad 1'000'000) :(";
    for(int i(0); i < str.length(); i++)
    {
        if(str[i] == 48)
            continue;
        tmp += dig(str[i]);
        if((str.length() - i - 1) % 3 == 1)
        {
            if(str[i] == 49)
            {
                tmp.erase(tmp.end() - 6, tmp.end());
                tmp += dig(str[i + 1]);
                if(str[i + 1] != 48)
                {
                    if(str[i + 1] != 50 && str[i + 1] != 52 && str[i + 1] != 55 && str[i + 1] != 56)
                        tmp.erase(tmp.end() - 1, tmp.end());
                    if(str[i + 1] == 52 || str[i + 1] == 57)
                        tmp += "t";
                    tmp += "nascie";
                }
                else
                    tmp += "dziesiec";
                i++;
            }
            else
            {
                if(str[i] == 50)
                    tmp += "dziescia";
                else if(str[i] == 51 || str[i] == 52)
                    tmp += "dziesci";
                else
                    tmp += "dziesat";
            }
        }
        else if((str.length() - i - 1) % 3 == 2)
        {
            if(str[i] == 49)
            {
                tmp.erase(tmp.end() - 6, tmp.end());
                tmp += " sto";
            }
            else
            {
                if(str[i] == 50)
                {
                    tmp.erase(tmp.end() - 1, tmp.end());
                    tmp += "iescie";
                }
                else if(str[i] == 51 || str[i] == 52)
                    tmp += "sta";
                else
                    tmp += "set";
            }
        }
        else if((str.length() - i - 1) == 3)
        {
            if(str[i] == 49)
            {
                tmp.erase(tmp.end() - 6, tmp.end());
                tmp += " tysiac";
            }
            else
            {
                if(str[i] == 50 || str[i] == 51 || str[i] == 52)
                    tmp += " tysiace";
                else
                    tmp += " tysiecy";
            }
        }
    }
    return tmp.c_str();
}

char *dig(int n){
    switch(n)
    {
    case 49:
        return " jeden";
    case 50:
        return " dwa";
    case 51:
        return " trzy";
    case 52:
        return " cztery";
    case 53:
        return " piec";
    case 54:
        return " szesc";
    case 55:
        return " siedem";
    case 56:
        return " osiem";
    case 57:
        return " dziewiec";
    default:
        return " ";
    }
}

int k(int n){
    /*
    ja nie wiem czy ja czegos nie zauwazam,
    bo zeby dojsc do tego wzoru to sie chyba godzine gapilem na wyniki podstawiania kolejnych liczb,
    sprawdzalem zaleznosci pomiedzy wielokrotnosciami, wspolnymi dzielnikami i przepisywalem to na system binarny,
    a i tak nie jest idealnie.
    */
    /*
    ta redukcja prawie nie wplywa na czas obliczen, a znaczaco zwieksza precyzje,
    jest w stanie znalezc rozwiazania dla np. k(144) = 7'716'049'375 (5 * k(72)) tylko ze przekraczaja zakres signed int
    pewnie by sie dalo zrobic na unsigned, chociaz ujemny zakres jest wykorzystywany (jako informacja ze zakres jest przekroczony)
    ma wyswietlac wynik miedzy 0 - 1'000'000 wiec nie ma potrzeby przerabiac na unsigned, long long czy cos
    */
    int _k(0), div_2(0), div_5(0);
    {
        int tmp(n);
        while(tmp > 0 && ((tmp % 10) == 0 || (tmp % 10) == 1))
            tmp /= 10;
        if(tmp == 0)
            return 1;
    }
    while(n % 10 == 0)
        n /= 10;
    while(n % 2 == 0 && n != 0)
    {
        n /= 2;
        div_2++;
    }
    while(n % 5 == 0 && n != 0)
    {
        n /= 5;
        div_5++;
    }
    _k = k_manual(n);
    while(div_2-- > 0)
        _k *= 5;
    while(div_5-- > 0)
        _k *= 2;
    if(_k < 0)
        return 0;
    return _k;
}

int k_manual(int n){
    for(int i(0), p(0), _k(1); n > 0 && i < 0b1111111111; i++, _k++)
    {
        for(p = 0; ;p++)
        {
            if(int(_k / pow(10, p)) % 10 == 2)
            {
                _k -= 2 * pow(10, p);
                _k += pow(10, p + 1);
            }
            else
                break;
        }
        if(_k % n == 0)
        {
            _k /= n;
            return _k;
        }
    }
    return 0;
}

int k_manual_old(int n){//goto zadania wymagaja goto rozwiazan
    int tmp(0), _k(1);
    while(_k++ > 0)
    {
        tmp = _k * n;
        if(tmp < 0)
            return 0;
        while(tmp > 0 && ((tmp % 10) == 0 || (tmp % 10) == 1))
            tmp /= 10;
        if(tmp == 0)
            break;
    }
    return _k;
}

int pow(int a, int b){//około 1% poprawy wzgledem pow() z math.h
    int c(a);
    if(b == 0)
        return 1;
    b--;
    while(b-- > 0)
        c *= a;
    return c;
}
