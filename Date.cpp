#include <iostream>
#include "Date.h"

Date::Date() {}
Date::Date(int d, int m, int y) {
    if (m<1 || m>12)
        throw "Invalid month";
    if (y<0 || y>2025)
        throw "Invalid year";
    if (d<1 || d>31)
        throw "Invalid day";
    if (d>30 && ((m%2==0 && m<7)||(m%2==0 && m>8)))
        throw "Invalid day";
    if (d>29 && m==2)
        throw "Invalid day";

    day = d;
    month = m;
    year = y;
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::print() const {
    std::cout << day << "/" << month << "/" << year << std::endl;
}

