#ifndef REGION_HXX
#define REGION_HXX


#include <string>
#include <iostream>


class Region {
private:
    std::string region_name;
    std::string date;
    unsigned long long start_count;
    unsigned long long was_born;
    unsigned long long was_died;
    unsigned long long immigration;
    unsigned long long emigration;
public:
    Region (void) noexcept;
    Region (const std::string& region_name, const std::string& date, const unsigned long long start_count, const unsigned long long was_born, const unsigned long long was_died, const unsigned long long immigration, const unsigned long long emigration) noexcept;
    ~Region (void) noexcept = default;
    Region& operator= (const Region& unit) noexcept;
    friend std::ostream& operator<< (std::ostream& os, const Region& unit);
    std::string getRegionName (void) const noexcept;
    std::string getDate (void) const noexcept;
    unsigned long long getStartCount (void) const noexcept;
    unsigned long long getWasBorn (void) const noexcept;
    unsigned long long getWasDied (void) const noexcept;
    unsigned long long getImmigration (void) const noexcept;
    unsigned long long getEmigration (void) const noexcept;
    void setRegionName (const std::string& region_name) noexcept;
    void setDate (const std::string& date) noexcept;
    void setStartCount (const unsigned long long start_count) noexcept;
    void setWasBorn (const unsigned long long was_born) noexcept;
    void setWasDied (const unsigned long long was_died) noexcept;
    void setImmigration (const unsigned long long immigration) noexcept;
    void setEmigration (const unsigned long long emigration) noexcept;
};

#endif // REGION_HXX