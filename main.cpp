#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class DirectoryEntry {
private:
    string companyName;
    string ownerName;
    string phoneNumber;
    string address;
    string businessType;

public:
    DirectoryEntry() {}

    DirectoryEntry(const string& company, const string& owner, const string& phone, const string& addr, const string& type)
        : companyName(company), ownerName(owner), phoneNumber(phone), address(addr), businessType(type) {}

    void setCompanyName(const string& company) { companyName = company; }
    void setOwnerName(const string& owner) { ownerName = owner; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setAddress(const string& addr) { address = addr; }
    void setBusinessType(const string& type) { businessType = type; }

    string getCompanyName() const { return companyName; }
    string getOwnerName() const { return ownerName; }
    string getPhoneNumber() const { return phoneNumber; }
    string getAddress() const { return address; }
    string getBusinessType() const { return businessType; }

    friend ostream& operator<<(ostream& out, const DirectoryEntry& entry) {
        out << "Company Name: " << entry.companyName << endl;
        out << "Owner: " << entry.ownerName << endl;
        out << "Phone Number: " << entry.phoneNumber << endl;
        out << "Address: " << entry.address << endl;
        out << "Business Type: " << entry.businessType << endl;
        return out;
    }
};

class Directory {
private:
    vector<DirectoryEntry> entries;
    string filename;

public:
    Directory(const string& fname) : filename(fname) {}

    bool addEntry(const DirectoryEntry& entry) {
        entries.push_back(entry);
        return true;
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Unable to open file for writing." << endl;
            return;
        }

        for (const auto& entry : entries) {
            file << entry.getCompanyName() << endl;
            file << entry.getOwnerName() << endl;
            file << entry.getPhoneNumber() << endl;
            file << entry.getAddress() << endl;
            file << entry.getBusinessType() << endl;
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Unable to open file for reading." << endl;
            return;
        }

        entries.clear();

        string company, owner, phone, address, type;
        while (getline(file, company)) {
            getline(file, owner);
            getline(file, phone);
            getline(file, address);
            getline(file, type);

            DirectoryEntry entry(company, owner, phone, address, type);
            entries.push_back(entry);
        }

        file.close();
    }

    void searchByName(const string& name) {
        bool found = false;
        for (const auto& entry : entries) {
            if (entry.getCompanyName() == name) {
                cout << entry << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Company with name '" << name << "' not found." << endl;
        }
    }

    void searchByOwner(const string& owner) {
        bool found = false;
        for (const auto& entry : entries) {
            if (entry.getOwnerName() == owner) {
                cout << entry << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Companies owned by '" << owner << "' not found." << endl;
        }
    }

    void searchByPhoneNumber(const string& phone) {
        bool found = false;
        for (const auto& entry : entries) {
            if (entry.getPhoneNumber() == phone) {
                cout << entry << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Company with phone number '" << phone << "' not found." << endl;
        }
    }

    void searchByBusinessType(const string& type) {
        bool found = false;
        for (const auto& entry : entries) {
            if (entry.getBusinessType() == type) {
                cout << entry << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Companies with business type '" << type << "' not found." << endl;
        }
    }

    void printAllEntries() {
        for (const auto& entry : entries) {
            cout << entry << endl;
        }
        cout << "Total entries: " << entries.size() << endl;
    }
};

int main() {
    Directory directory("directory.txt");

    DirectoryEntry entry1("Company1", "Owner1", "111-111-1111", "Address1", "Type1");
    DirectoryEntry entry2("Company2", "Owner2", "222-222-2222", "Address2", "Type2");
    DirectoryEntry entry3("Company3", "Owner3", "333-333-3333", "Address3", "Type1");

    directory.addEntry(entry1);
    directory.addEntry(entry2);
    directory.addEntry(entry3);

    directory.saveToFile();
    directory.loadFromFile();

    cout << "Search by name 'Company2':" << endl;
    directory.searchByName("Company2");

    cout << "\nSearch by owner 'Owner3':" << endl;
    directory.searchByOwner("Owner3");

    cout << "\nSearch by phone number '111-111-1111':" << endl;
    directory.searchByPhoneNumber("111-111-1111");

    cout << "\nSearch by business type 'Type1':" << endl;
    directory.searchByBusinessType("Type1");

    cout << "\nAll entries in the directory:" << endl;
    directory.printAllEntries();

    return 0;
}
