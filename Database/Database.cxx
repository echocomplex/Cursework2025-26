#include "Database.hxx"

Database::Database (void) {
    this->filename = "database.txt";
    this->filename_enc = "database.enc";
    this->crypter.decrypt(this->filename_enc, this->filename);
    this->file.open(this->filename, true);
    this->file.readToList(this->data);
}

Database::Database (const std::string& filename) {
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->crypter.encrypt(this->filename_enc, this->filename);
    this->file.open(filename);
    this->file.readToList(this->data);
}

Database::Database (const List <Region>& unit, const std::string& filename) {
    this->data = unit;
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->file.open(this->filename);
}

Database::Database (const Database& unit) {
    this->data = unit.data;
    this->file.open(unit.filename);
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
}

Database::~Database (void) {
    this->file.rewriteFromList(this->data);
    this->crypter.encrypt(this->filename, this->filename_enc);
}

Database& Database::operator= (const Database& unit) noexcept {
    if (this == &unit) return *this;
    this->data = unit.data;
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
    this->file.open(unit.filename);
    return *this;
}

Region& Database::operator[] (const unsigned int index) noexcept {
    return this->data[index];
}

std::ostream& operator<< (std::ostream& os, const Database& unit) {
    for (unsigned int i = 0; i < unit.data.length(); ++i) os << i + 1 << ' ' << unit[i] << std::endl;
    return os;
}

const Region& Database::operator[] (const unsigned int index) const noexcept {
    return this->data[index];
}

void Database::append (const Region& unit) noexcept {
    this->data.append(unit);
}

void Database::remove (const unsigned int index) noexcept {
    this->data.remove(index);
}

unsigned int Database::size () noexcept {
    return this->data.length();
}

void Database::getRegionsInformation (List <std::pair <Region, long long>>& unit) const noexcept {
    std::pair <Region, long long> current_pair;
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Region& current = this->data[i];
        current_pair.first = current;
        current_pair.second = current.getWasBorn() - current.getWasDied();
        unit.append(current_pair);
    }
}

void Database::getRegionsWithCalculatedSaldo (List <std::pair <Region, long long>>& unit) const noexcept {
    std::pair <Region, long long> current_pair;
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Region& current = this->data[i];
        current_pair.first = current;
        current_pair.second = current.getImmigration() - current.getEmigration();
        unit.append(current_pair);
    }
}

unsigned short Database::countBigRegions (void) const noexcept {
    double avg = 0.0;
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Region& current = this->data[i];
        avg += current.getStartCount() + ((current.getWasBorn() - current.getWasDied()) + (current.getImmigration() - current.getEmigration()));
    }
    avg /= this->data.length();

    unsigned int count = 0;
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Region& current = this->data[i];
        if (avg < current.getStartCount() + ((current.getWasBorn() - current.getWasDied()) + (current.getImmigration() - current.getEmigration()))) ++count;
    }
    return count;
}