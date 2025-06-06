#include <iostream>
#include "Incident.h"

Incident::Incident() : id(""), area(""), type(""), description(""), date() {}

Incident::Incident(const std::string& id, const std::string& area,
                   const std::string& type, const std::string& desc, const Date& date)
    : id(id), area(area), type(type), description(desc), date(date) {}

void Incident::print() const {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string CYAN = "\033[36m";

    std::cout << "Incident ID: " << RED << id << RESET << std::endl;
    std::cout << "Area: " << GREEN << area << RESET << std::endl;
    std::cout << "Type: " << YELLOW << type << RESET << std::endl;
    std::cout << "Description: " << CYAN << description << RESET << std::endl;
    std::cout << "Date: ";
    date.print();
}

std::string Incident::getId() const { return id; }
std::string Incident::getArea() const { return area; }
std::string Incident::getType() const { return type; }
std::string Incident::getDescription() const { return description; }
Date Incident::getDate() const { return date; }

void Incident::setId(const std::string& val) { id = val; }
void Incident::setArea(const std::string& val) { area = val; }
void Incident::setType(const std::string& val) { type = val; }
void Incident::setDescription(const std::string& val) { description = val; }
void Incident::setDate(const Date& val) { date = val; }

