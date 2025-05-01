#include "Interface.hxx"

void Interface::clearInputBuffer (void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Interface::getRegion (Region& unit) {
    std::string temp;
    unsigned short temp_number = 0;

    std::cout << "Enter the Region Name: ";
    std::getline(std::cin, temp);
    unit.setRegionName(temp);
    std::cout << "Enter the Date: ";
    std::getline(std::cin, temp);
    unit.setDate(temp);
    std::cout << "Enter the Start Count: ";
    std::cin >> temp_number;
    this->clearInputBuffer();
    unit.setStartCount(temp_number);
    temp_number = 0;
    std::cout << "Enter how much was born: ";
    std::cin >> temp_number;
    this->clearInputBuffer();
    unit.setWasBorn(temp_number);
    temp_number = 0;
    std::cout << "Enter how much was died: ";
    std::cin >> temp_number;
    this->clearInputBuffer();
    unit.setWasDied(temp_number);
    std::cout << "Enter how much was immigrated: ";
    std::cin >> temp_number;
    this->clearInputBuffer();
    unit.setImmigration(temp_number);
    std::cout << "Enter how much was emigrated: ";
    std::cin >> temp_number;
    this->clearInputBuffer();
    unit.setEmigration(temp_number);
}

int Interface::removeRegion (void) {
    int number;
    while (true) {
        std::cout << "Enter Region number to delete (1-" << this->unit.size() << "): ";
        
        if (!(std::cin >> number)) {
            std::cin.clear();
            this->clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }

        if (number > 0 && number <= this->unit.size()) {
            return number - 1;
        }
        
        std::cerr << "Error: Number must be between 1 and " << this->unit.size() << "\n\n";
    }
}

void Interface::displayMenu (void) {
    std::cout << "\n\n=== Region Database Menu ===" << std::endl;
    std::cout << "1. Display all records" << std::endl;
    std::cout << "2. Add new Region" << std::endl;
    std::cout << "3. Remove Region" << std::endl;
    std::cout << "4. Display Regions With Population Growth" << std::endl;
    std::cout << "5. Display Regions With Calculated Saldo" << std::endl;
    std::cout << "6. Count Big Regions (regions with population > avg)" << std::endl;
    std::cout << "7. Exit program" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Interface::pool (void) {
    short choice = 0;
    List <std::pair <Region, long long>> collected;
    Region new_region;
    while (true) {
        this->displayMenu();

        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Invalid input. Please enter 1-7: ";
            this->clearInputBuffer();
        }

        this->clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "\n[Displaying all records]\n";
                std::cout << this->unit << std::endl;
                break;
            case 2:
                std::cout << "\n[Adding new Region]\n";
                this->getRegion(new_region);
                this->unit.append(new_region);
                break;
            case 3:
                std::cout << "\n[Removing Region]\n";
                this->unit.remove(this->removeRegion());
                break;
            case 4:
                std::cout << "\n[Displaying Regions With Population Growth]\n";
                this->unit.getRegionsInformation(collected);
                for (int i = 0; i < collected.length(); ++i) std::cout << collected[i].first << ", Growth: " << collected[i].second << std::endl;
                collected.clear();
                break;
            case 5:
                std::cout << "\n[Displaying Regions With Calculated Saldo]\n";
                this->unit.getRegionsWithCalculatedSaldo(collected);
                for (int i = 0; i < collected.length(); ++i) std::cout << collected[i].first << ", Saldo: " << collected[i].second << std::endl;
                collected.clear();
                break;
            case 6:
                std::cout << "There's " << this->unit.countBigRegions() << " Regions > avg" << std::endl;
                break;
            case 7:
                std::cout << "\nExiting program...\n";
                return;
        }

        std::cout << "\nOperation completed. Press Enter to continue...";
        this->clearInputBuffer();
    }
}