#ifndef INCIDENT_H
#define INCIDENT_H

#include <string>
#include "Date.h"

class Incident {
private:
    std::string id, area, type, description;
    Date date;

public:
    Incident();
    Incident(const std::string& id, const std::string& area, const std::string& type,
             const std::string& desc, const Date& date);

    void print() const;
    // Accessors
    std::string getId() const;
    std::string getArea() const;
    std::string getType() const;
    std::string getDescription() const;
    Date getDate() const;

    // Mutators
    void setId(const std::string& val);
    void setArea(const std::string& val);
    void setType(const std::string& val);
    void setDescription(const std::string& val);
    void setDate(const Date& val);

};

#endif

