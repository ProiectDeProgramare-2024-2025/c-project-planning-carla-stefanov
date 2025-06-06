#ifndef DATE_H
#define DATE_H

class Date {
private:
    int day, month, year;

public:
    Date();
    Date(int d, int m, int y); // parameterized constructor

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void print() const;
};

#endif // DATE_H

