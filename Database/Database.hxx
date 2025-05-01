#ifndef DATABASE_HXX
#define DATABASE_HXX


#include <List.hxx>
#include <Region.hxx>
#include <Filer.hxx>
#include <iostream>
#include <Crypter.hxx>
#include <ctime>


class Database {
protected:
    Filer file;
    std::string filename;
    std::string filename_enc;
    List <Region> data;
    Crypter crypter;
public:
    Database (void);
    Database (const std::string& filename);
    Database (const List <Region>& unit, const std::string& filename);
    Database (const Database& unit);
    ~Database (void);
    Database& operator= (const Database& unit) noexcept;
    Region& operator[] (const unsigned int index) noexcept;
    friend std::ostream& operator<< (std::ostream& os, const Database& unit);
    const Region& operator[] (const unsigned int index) const noexcept;
    void append (const Region& unit) noexcept;
    void remove (const unsigned int index) noexcept;
    unsigned int size (void) noexcept;
    void getRegionsInformation (List <std::pair <Region, long long>>& unit) const noexcept;
    void getRegionsWithCalculatedSaldo (List <std::pair <Region, long long>>& unit) const noexcept;
    unsigned short countBigRegions (void) const noexcept;
};


#endif // DATABASE_HXX