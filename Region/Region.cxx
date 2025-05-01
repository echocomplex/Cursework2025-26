#include "Region.hxx"

Region::Region (void) noexcept {
    this->start_count = 0;
    this->was_born = 0;
    this->was_died = 0;
    this->immigration = 0;
    this->emigration = 0;
}
    
Region::Region (const std::string& region_name, const std::string& date, const unsigned long long start_count, const unsigned long long was_born, const unsigned long long was_died, const unsigned long long immigration, const unsigned long long emigration) noexcept {
    this->region_name = region_name;
    this->date = date;
    this->start_count = start_count;
    this->was_born = was_born;
    this->was_died = was_died;
    this->immigration = immigration;
    this->emigration = emigration;
}

Region& Region::operator= (const Region& unit) noexcept {
    this->region_name = unit.region_name;
    this->date = unit.date;
    this->start_count = unit.start_count;
    this->was_born = unit.was_born;
    this->was_died = unit.was_died;
    this->immigration = unit.immigration;
    this->emigration = unit.emigration;
    return *this;
}
std::ostream& operator<< (std::ostream& os, const Region& unit) {
    os << 
        unit.region_name << ", " <<
        unit.date << ", " <<
        unit.start_count << ", " <<
        unit.was_born << ", " <<
        unit.was_died << ", " <<
        unit.immigration << ", " <<
        unit.emigration
    ;
    return os;
}

std::string Region::getRegionName (void) const noexcept {
    return this->region_name;
}

std::string Region::getDate (void) const noexcept {
    return this->date;
}

unsigned long long Region::getStartCount (void) const noexcept {
    return this->start_count;
}

unsigned long long Region::getWasBorn (void) const noexcept {
    return this->was_born;
}
    
unsigned long long Region::getWasDied (void) const noexcept {
    return this->was_died;
}
    
unsigned long long Region::getImmigration (void) const noexcept {
    return this->immigration;
}

unsigned long long Region::getEmigration (void) const noexcept {
    return this->emigration;
}
    
void Region::setRegionName (const std::string& region_name) noexcept {
    this->region_name = region_name;
}
    
void Region::setDate (const std::string& date) noexcept {
    this->date = date;
}
    
void Region::setStartCount (const unsigned long long start_count) noexcept {
    this->start_count = start_count;
}
    
void Region::setWasBorn (const unsigned long long was_born) noexcept {
    this->was_born = was_born;
}
    
void Region::setWasDied (const unsigned long long was_died) noexcept {
    this->was_died = was_died;
}
    
void Region::setImmigration (const unsigned long long immigration) noexcept {
    this->immigration = immigration;
}
    
void Region::setEmigration (const unsigned long long emigration) noexcept {
    this->emigration = emigration;
}