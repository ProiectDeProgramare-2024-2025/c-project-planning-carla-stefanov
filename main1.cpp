#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Date.h"
#include "Incident.h"

using namespace std;

// Utility functions for color output
void printSuccess(const string& msg) {
    cout << "\033[1;32m" << msg << "\033[0m\n";
}

void printError(const string& msg) {
    cerr << "\033[1;31mError: " << msg << "\033[0m\n";
}

vector<Incident> loadIncidents(const string& filename) {
    ifstream fin(filename);
    vector<Incident> incidents;
    if (!fin) return incidents;

    try {
        int count;
        fin >> count;
        fin.ignore();

        for (int i = 0; i < count; ++i) {
            string id, area, type, description;
            int day, month, year;

            fin >> id >> area >> type;
            fin.ignore();
            getline(fin, description);
            fin >> day >> month >> year;
            fin.ignore();

            Date date(day, month, year);
            Incident inc(id, area, type, description, date);
            incidents.push_back(inc);
        }
    } catch (const exception& e) {
        printError("Failed to load incidents: " + string(e.what()));
    }

    return incidents;
}

void saveIncidents(const vector<Incident>& incidents, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        printError("Unable to open file for writing.");
        return;
    }

    fout << incidents.size() << '\n';
    for (const auto& inc : incidents) {
        Date date = inc.getDate();
        fout << inc.getId() << ' ' << inc.getArea() << ' ' << inc.getType() << '\n'
             << inc.getDescription() << '\n'
             << date.getDay() << ' ' << date.getMonth() << ' ' << date.getYear() << '\n';
    }
}

void viewAll() {
    auto incidents = loadIncidents("incidents.txt");
    if (incidents.empty()) {
        printError("No incidents found.");
        return;
    }
    for (const auto& inc : incidents) inc.print();
}

void addIncident(int argc, char* argv[]) {
    if (argc < 9) {
        printError("Usage: add_incident <id> <area> <type> <description> <day> <month> <year>");
        return;
    }

    try {
        string id = argv[2];
        string area = argv[3];
        string type = argv[4];
        string description = argv[5];
        int day = stoi(argv[6]);
        int month = stoi(argv[7]);
        int year = stoi(argv[8]);

        Date date(day, month, year);
        Incident inc(id, area, type, description, date);

        auto incidents = loadIncidents("incidents.txt");
        incidents.push_back(inc);
        saveIncidents(incidents, "incidents.txt");
        printSuccess("Incident added successfully.");
    } catch (const exception& e) {
        printError("Failed to add incident: " + string(e.what()));
    }
}

void deleteIncident(const string& id) {
    auto incidents = loadIncidents("incidents.txt");
    vector<Incident> updated;

    for (const auto& inc : incidents) {
        if (inc.getId() != id)
            updated.push_back(inc);
    }

    saveIncidents(updated, "incidents.txt");
    printSuccess("Incident deleted if it existed.");
}

void updateIncident(int argc, char* argv[]) {
    if (argc < 5) {
        printError("Usage: update_incident <id> <field> <new_value>");
        return;
    }

    string id = argv[2], field = argv[3];
    auto incidents = loadIncidents("incidents.txt");
    bool found = false;

    for (auto& inc : incidents) {
        if (inc.getId() == id) {
            found = true;
            if (field == "area") {
                inc.setArea(argv[4]);
            } else if (field == "type") {
                inc.setType(argv[4]);
            } else if (field == "description") {
                inc.setDescription(argv[4]);
            } else if (field == "date") {
                if (argc < 7) {
                    printError("Usage: update_incident <id> date <day> <month> <year>");
                    return;
                }
                int d = stoi(argv[4]), m = stoi(argv[5]), y = stoi(argv[6]);
                inc.setDate(Date(d, m, y));
            } else {
                printError("Invalid field name.");
                return;
            }
        }
    }

    if (found) {
        saveIncidents(incidents, "incidents.txt");
        printSuccess("Incident updated.");
    } else {
        printError("Incident not found.");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printError("Usage: ./app_admin.exe <command> [...args]");
        return 1;
    }

    string command = argv[1];

    if (command == "view_all_incidents") {
        viewAll();
    } else if (command == "add_incident") {
        addIncident(argc, argv);
    } else if (command == "delete_incident" && argc >= 3) {
        deleteIncident(argv[2]);
    } else if (command == "update_incident") {
        updateIncident(argc, argv);
    } else {
        printError("Unknown or incomplete command.");
    }

    return 0;
}
