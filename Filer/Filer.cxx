#include "Filer.hxx"

Filer::Filer (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

Filer::~Filer (void) noexcept {
    if (this->file.is_open()) this->file.close();
}

void Filer::open (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

void Filer::read (std::string& str) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;

    this->file.seekp(0, std::ios::beg);
    while (std::getline(this->file, temp)) str += temp + '\n';
    
    this->mutex.unlock();
}

void Filer::readToList (List <Region>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;
    Region node;
    while (std::getline(this->file, temp)) {
        node = Region();
        this->stringToRegion(node, temp);
        unit.append(node);
    }

    this->mutex.unlock();
}

void Filer::writeBack (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << string << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::writeBackFromRegion (const Region& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << 
        unit.getRegionName() << "$$" <<
        unit.getDate() << "$$" <<
        unit.getStartCount() << "$$" <<
        unit.getWasBorn() << "$$" <<
        unit.getWasDied() << "$$" <<
        unit.getImmigration() << "$$" <<
        unit.getEmigration() << '\n'
    ;
    this->file.flush();
    
    this->mutex.unlock();
}

void Filer::rewrite (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file << string << '\n';
    this->file.flush();

    this->mutex.unlock();
}

void Filer::rewriteFromList (const List <Region>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (unit.length() == 0) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file.seekg(0, std::ios::beg);

    for (unsigned int i = 0; i < unit.length(); ++i) {
        this->file << 
            unit[i].getRegionName() << "$$" <<
            unit[i].getDate() << "$$" <<
            unit[i].getStartCount() << "$$" <<
            unit[i].getWasBorn() << "$$" <<
            unit[i].getWasDied() << "$$" <<
            unit[i].getImmigration() << "$$" <<
            unit[i].getEmigration() << '\n'
        ;
    }
    this->file.flush();

    this->mutex.unlock();
}

void Filer::stringToRegion (Region& unit, const std::string& str) {
    if (str.empty()) return;

    std::string arr[7];
    unsigned short count = 0;
    for (size_t i = 0; i < (str.size() - 1) && count < 7; ++i) {
        if (str[i] == '$' && str[i + 1] == '$') {
            ++count, ++i;
        } 
        else arr[count].push_back(str[i]);
    }
    if (count < 7) arr[count].push_back(str[str.size() - 1]);

    unit.setRegionName(arr[0]);
    unit.setDate(arr[1]);
    try {
        unit.setStartCount(std::stoul(arr[2]));
    } 
    catch (std::exception) {
        unit.setStartCount(0); 
    }
    try {
        unit.setWasBorn(std::stoul(arr[3]));
    } 
    catch (std::exception) {
        unit.setWasBorn(0); 
    }
    try {
        unit.setWasDied(std::stoul(arr[4]));
    } 
    catch (std::exception) {
        unit.setWasDied(0); 
    }
    try {
        unit.setImmigration(std::stoul(arr[5]));
    } 
    catch (std::exception) {
        unit.setImmigration(0); 
    }
    try {
        unit.setEmigration(std::stoul(arr[6]));
    } 
    catch (std::exception) {
        unit.setEmigration(0); 
    }
}
