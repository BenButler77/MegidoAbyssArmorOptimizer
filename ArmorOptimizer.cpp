// ArmorOptimizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;

class Armor {
    private:
        int phys, fire, water, earth, wind, poison, bleed, slow;
        string name, id;
    public:
        Armor();
        Armor(int p, int f, int w, int e, int wi, int po, int bl, int sl, string i, string n) {
            phys = p;
            fire = f;
            water = w;
            earth = e;
            wind = wi;
            poison = po;
            bleed = bl;
            slow = sl;
            name = n;
            id = i;
        }
        int getPhys() {
            return phys;
        }
        int getFire() {
            return fire;
        }
        int getWater() {
            return water;
        }
        int getEarth() {
            return earth;
        }
        int getWind() {
            return wind;
        }
        int getPoison() {
            return poison;
        }
        int getBleed() {
            return bleed;
        }
        int getSlow() {
            return slow;
        }
        string getName() {
            return name;
        }
        string getID() {
            return id;
        }
};

class ArmorSet {
    public:
        Armor* helm;
        Armor* chestplate;
        Armor* leggings;
        Armor* boots;;

        ArmorSet(Armor* h, Armor* c, Armor* l, Armor* b) {
            helm = h;
            chestplate = c;
            leggings = l;
            boots = b;
        }
        int getTotalPhys() {
            return helm->getPhys() + chestplate->getPhys() + leggings->getPhys() + boots->getPhys();
        }
        int getTotalFire() {
            return helm->getFire() + chestplate->getFire() + leggings->getFire() + boots->getFire();
        }
        int getTotalWater() {
            return helm->getWater() + chestplate->getWater() + leggings->getWater() + boots->getWater();
        }
        int getTotalEarth() {
            return helm->getEarth() + chestplate->getEarth() + leggings->getEarth() + boots->getEarth();
        }
        int getTotalWind() {
            return helm->getWind() + chestplate->getWind() + leggings->getWind() + boots->getWind();
        }
        int getTotalPoison() {
            return helm->getPoison() + chestplate->getPoison() + leggings->getPoison() + boots->getPoison();
        }
        int getTotalBleed() {
            return helm->getBleed() + chestplate->getBleed() + leggings->getBleed() + boots->getBleed();
        }
        int getTotalSlow() {
            return helm->getSlow() + chestplate->getSlow() + leggings->getSlow() + boots->getSlow();
        }
};

int validatedIntInput(int min, int max, string error) {
    int input = 0;
    while (true) {
        cin >> input;
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << error;
            std::cin >> input;
        }
        if (input < min || input > max)
        {
            std::cout << error;
        }
        else
            break;
    }
    return input;
}

vector<string> validatedMinInput() {
    string input, temp;
    vector<string> result;
    int check;
    bool invalid = false;
    cin.ignore();
    do {
        invalid = false;
        result.clear();
        std::getline(std::cin, input);
        while (input.find(" ") != string::npos) {
            temp = input.substr(0, input.find(" "));
            result.push_back(temp);
            input = input.substr(input.find(" ") + 1);
        }
        result.push_back(input);
        if (result.size() == 8) {
            for (string i : result) {
                if (i != "X" && i != "x") {
                    try {
                        check = stoi(i);
                    }
                    catch (exception& err) {
                        invalid = true;
                        cout << "Input must be 8 numbers or \"X\"s separated by spaces.\n";
                        cout << "Enter: ";
                        break;
                    }
                }
            }
        }
        else {
            invalid = true;
            cout << "Input must be 8 numbers or \"X\"s separated by spaces.\n";
            cout << "Enter: ";
        }
    } while (invalid);
    return result;
}

vector<ArmorSet*> findOptimalSets(string optimize, vector<Armor*> helmCatalogue, vector<Armor*> chestplateCatalogue, vector<Armor*> leggingsCatalogue, vector<Armor*> bootsCatalogue, Armor* requiredHelm, Armor* requiredChestplate, Armor* requiredLeggings, Armor* requiredBoots, vector<string> minimumValuesInput) {
    int max = -100;
    int check = 0;
    vector<int> minimumValues;
    for (string i : minimumValuesInput) {
        if (i == "X" || i == "x")
            minimumValues.push_back(-100);
        else
            minimumValues.push_back(stoi(i));
    }
    vector<ArmorSet*> optimalSets;
    int helmetSet = 0, chestplateSet = 0, leggingsSet = 0, bootsSet = 0;

    if (requiredHelm->getName() != "N/A") {
        helmetSet = 1;
    }
    if (requiredChestplate->getName() != "N/A") {
        chestplateSet = 1;
    }
    if (requiredLeggings->getName() != "N/A") {
        leggingsSet = 1;
    }
    if (requiredBoots->getName() != "N/A") {
        bootsSet = 1;
    }
    cout << "Finding optimal sets. Please wait...";

    for (Armor* helm : helmCatalogue) {
        for (Armor* chestplate : chestplateCatalogue) {
            for (Armor* leggings : leggingsCatalogue) {
                for (Armor* boots : bootsCatalogue) {
                    if (helmetSet)
                        helm = requiredHelm;
                    if (chestplateSet)
                        chestplate = requiredChestplate;
                    if (leggingsSet)
                        leggings = requiredLeggings;
                    if (bootsSet)
                        boots = requiredBoots;
                    if (optimize == "Physical") {
                        check = helm->getPhys() + chestplate->getPhys() + leggings->getPhys() + boots->getPhys();
                    }
                    else if (optimize == "Fire") {
                        check = helm->getFire() + chestplate->getFire() + leggings->getFire() + boots->getFire();
                    }
                    else if (optimize == "Water") {
                        check = helm->getWater() + chestplate->getWater() + leggings->getWater() + boots->getWater();
                    }
                    else if (optimize == "Earth") {
                        check = helm->getEarth() + chestplate->getEarth() + leggings->getEarth() + boots->getEarth();
                    }
                    else if (optimize == "Wind") {
                        check = helm->getWind() + chestplate->getWind() + leggings->getWind() + boots->getWind();
                    }
                    else if (optimize == "Poison") {
                        check = helm->getPoison() + chestplate->getPoison() + leggings->getPoison() + boots->getPoison();
                    }
                    else if (optimize == "Bleed") {
                        check = helm->getBleed() + chestplate->getBleed() + leggings->getBleed() + boots->getBleed();
                    }
                    else if (optimize == "Slow") {
                        check = helm->getSlow() + chestplate->getSlow() + leggings->getSlow() + boots->getSlow();
                    }
                    if (check >= max) {
                        if (helm->getPhys() + chestplate->getPhys() + leggings->getPhys() + boots->getPhys() >= minimumValues.at(0) && helm->getFire() + chestplate->getFire() + leggings->getFire() + boots->getFire() >= minimumValues.at(1) && helm->getWater() + chestplate->getWater() + leggings->getWater() + boots->getWater() >= minimumValues.at(2) && helm->getEarth() + chestplate->getEarth() + leggings->getEarth() + boots->getEarth() >= minimumValues.at(3) && helm->getWind() + chestplate->getWind() + leggings->getWind() + boots->getWind() >= minimumValues.at(4) && helm->getPoison() + chestplate->getPoison() + leggings->getPoison() + boots->getPoison() >= minimumValues.at(5) && helm->getBleed() + chestplate->getBleed() + leggings->getBleed() + boots->getBleed() >= minimumValues.at(6) && helm->getSlow() + chestplate->getSlow() + leggings->getSlow() + boots->getSlow() >= minimumValues.at(7)) {
                            if (check > max) {
                                max = check;
                                optimalSets.clear();
                                optimalSets.push_back(new ArmorSet(helm, chestplate, leggings, boots));
                            }
                            else {
                                optimalSets.push_back(new ArmorSet(helm, chestplate, leggings, boots));
                            }
                        }
                    }
                    if (bootsSet)
                        break;
                }
                if (leggingsSet)
                    break;
            }
            if (chestplateSet)
                break;
        }
        if (helmetSet)
            break;
    }
    return optimalSets;
}

void displaySets(vector<ArmorSet*> optimalSets) {
    cout << endl << endl;
    if (optimalSets.empty()) {
        cout << "No sets found with the specifications provided." << endl;
    }
    else {
        for (ArmorSet* set : optimalSets) {
            cout << set->helm->getName() << " - Physical: " << set->helm->getPhys() << " Fire: " << set->helm->getFire() << " Water: " << set->helm->getWater() << " Earth: " << set->helm->getEarth() << " Wind: " << set->helm->getWind() << " Poison: " << set->helm->getPoison() << " Bleed: " << set->helm->getBleed() << " Slow: " << set->helm->getSlow() << endl;
            cout << set->chestplate->getName() << " - Physical: " << set->chestplate->getPhys() << " Fire: " << set->chestplate->getFire() << " Water: " << set->chestplate->getWater() << " Earth: " << set->chestplate->getEarth() << " Wind: " << set->chestplate->getWind() << " Poison: " << set->chestplate->getPoison() << " Bleed: " << set->chestplate->getBleed() << " Slow: " << set->chestplate->getSlow() << endl;
            cout << set->leggings->getName() << " - Physical: " << set->leggings->getPhys() << " Fire: " << set->leggings->getFire() << " Water: " << set->leggings->getWater() << " Earth: " << set->leggings->getEarth() << " Wind: " << set->leggings->getWind() << " Poison: " << set->leggings->getPoison() << " Bleed: " << set->leggings->getBleed() << " Slow: " << set->leggings->getSlow() << endl;
            cout << set->boots->getName() << " - Physical: " << set->boots->getPhys() << " Fire: " << set->boots->getFire() << " Water: " << set->boots->getWater() << " Earth: " << set->boots->getEarth() << " Wind: " << set->boots->getWind() << " Poison: " << set->boots->getPoison() << " Bleed: " << set->boots->getBleed() << " Slow: " << set->boots->getSlow() << endl;
            cout << "Total - Physical: " << set->getTotalPhys() << " Fire: " << set->getTotalFire() << " Water: " << set->getTotalWater() << " Earth: " << set->getTotalEarth() << " Wind: " << set->getTotalWind() << " Poison: " << set->getTotalPoison() << " Bleed: " << set->getTotalBleed() << " Slow: " << set->getTotalSlow() << endl << endl;
        }
    }
}

int main()
{
    vector<Armor*> helmCatalogue, chestplateCatalogue, leggingsCatalogue, bootsCatalogue;
    int phys = 0, fire = 0, water = 0, earth = 0, wind = 0, poison = 0, bleed = 0, slow = 0;
    string type = "", name = "", temp = "", id = "", line;
    ifstream myfile("armor.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line.find("#helm") != string::npos) {
                type = "helm";
            }
            else if (line.find("#chest") != string::npos) {
                type = "chest";
            }
            else if (line.find("#leg") != string::npos) {
                type = "leggings";
            }
            else if (line.find("#boot") != string::npos) {
                type = "boots";
            }
            else if (line.find("item.type") != string::npos) {
                temp = line.substr(line.find("::") + 2);
                id = temp.substr(0, temp.find("}"));
            }
            else if (line.find("item.phys") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                phys = stoi(temp);
            }
            else if (line.find("item.fire") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                fire = stoi(temp);
            }
            else if (line.find("item.wate") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                water = stoi(temp);
            }
            else if (line.find("item.eart") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                earth = stoi(temp);
            }
            else if (line.find("item.wind") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                wind = stoi(temp);
            }
            else if (line.find("item.pois") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                poison = stoi(temp);
            }
            else if (line.find("item.blee") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                bleed = stoi(temp);
            }
            else if (line.find("item.slow") != string::npos) {
                temp = line.substr(line.find("to ") + 3);
                slow = stoi(temp);
            }
            else if (line.find("set {id.") != string::npos) {
                temp = line.substr(line.find("set \{id.") + 8);
                name = temp.substr(0, temp.find("}"));
                Armor* armor = new Armor(phys, fire, water, earth, wind, poison, bleed, slow, id, name);
                if (type == "helm") {
                    helmCatalogue.push_back(armor);
                }
                else if (type == "chest") {
                    chestplateCatalogue.push_back(armor);
                }
                else if (type == "leggings") {
                    leggingsCatalogue.push_back(armor);
                }
                else if (type == "boots") {
                    bootsCatalogue.push_back(armor);
                }
            }
        }
    }

    myfile.close();
    int input = 0, input2 = 0;
    string input3 = "", search = "", search2 = "";
    vector<string> minimumValues = { "X", "X", "X", "X", "X", "X", "X", "X" };
    string optimize = "Physical";
    Armor* requiredHelm = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
    Armor* requiredChestplate = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
    Armor* requiredLeggings = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
    Armor* requiredBoots = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
    vector<ArmorSet*> optimalSets;
    do {
        system("cls");
        cout << "MENU\n[====================]\n1 - Change Optimized Stat (Current: " << optimize << ")\n2 - Enter Minimum Stats\n3 - Enter Required Armor Pieces\n4 - Display Optimized Sets\n5 - Clear Inputs\n6 - End\nEnter Command: ";
        input = validatedIntInput(1, 6, "Input must be a number between 1-6.\nEnter Command: ");
        if (input == 1) {
            cout << "Select a stat to optimize:\n1 - Phys\n2 - Fire\n3 - Water\n4 - Earth\n5 - Wind\n6 - Poison\n7 - Bleed\n8 - Slow\nSelection: ";
            input2 = validatedIntInput(1, 8, "Input must be a number between 1-8.\nSelection: ");
            if (input2 == 1)
                optimize = "Physical";
            else if (input2 == 2)
                optimize = "Fire";
            else if (input2 == 3)
                optimize = "Water";
            else if (input2 == 4)
                optimize = "Earth";
            else if (input2 == 5)
                optimize = "Wind";
            else if (input2 == 6)
                optimize = "Poison";
            else if (input2 == 7)
                optimize = "Bleed";
            else if (input2 == 8)
                optimize = "Slow";
        }
        else if (input == 2) {
            cout << "Enter 8 minimum values separated by a space. Enter X to denote no minimum value.\nPhysical Fire Water Earth Wind Poison Bleed Slow\nEnter: ";
            minimumValues = validatedMinInput();
            cout << "Minimum Physical: " << minimumValues.at(0) << "\nMinimum Fire: " << minimumValues.at(1) << "\nMinimum Water: " << minimumValues.at(2) << "\nMinimum Earth: " << minimumValues.at(3) << "\nMinimum Wind: " << minimumValues.at(4) << "\nMinimum Poison: " << minimumValues.at(5) << "\nMinimum Bleed: " << minimumValues.at(6) << "\nMinimum Slow: " << minimumValues.at(7) << endl;
            cout << "Press any key to continue...";
            _getch();
        }
        else if (input == 3) {
            cout << "Select an armor slot:\n1 - Helm\n2 - Chestplate\n3 - Leggings\n4 - Boots\nSelection: ";
            input2 = validatedIntInput(1, 4, "Input must be a number between 1-4.\nSelection: ");
            if (input2 == 1) {
                cout << "Enter the required helm's name or ID, or type 'clear' to clear: ";
                cin.ignore();
                getline(std::cin, input3);
                if (input3 == "clear") {
                    cout << "Required helm cleared.\n";
                    requiredHelm = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
                }
                else {
                    for (Armor* helm : helmCatalogue) {
                        search = helm->getName();
                        search2 = helm->getID();
                        if (search.find(input3) != string::npos || search2.find(input3) != string::npos)
                        {
                            requiredHelm = helm;
                            input2 = 0;
                            break;
                        }
                    }
                    if (input2 == 0)
                        cout << "Required helm set to " << requiredHelm->getName() << ".\n";
                    else
                        cout << "Helm not found.\n";
                }
                cout << "Press any key to continue...";
                _getch();
            }
            else if (input2 == 2) {
                cout << "Enter the required chestplate's name or ID, or type 'clear' to clear: ";
                cin.ignore();
                getline(std::cin, input3);
                if (input3 == "clear") {
                    cout << "Required chestplate cleared.\n";
                    requiredChestplate = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
                }
                else {
                    for (Armor* chestplate : chestplateCatalogue) {
                        search = chestplate->getName();
                        search2 = chestplate->getID();
                        if (search.find(input3) != string::npos || search2.find(input3) != string::npos)
                        {
                            requiredChestplate = chestplate;
                            input2 = 0;
                            break;
                        }
                    }
                    if (input2 == 0)
                        cout << "Required chestplate set to " << requiredChestplate->getName() << ".\n";
                    else
                        cout << "Chestplate not found.\n";
                }
                cout << "Press any key to continue...";
                _getch();
            }
            else if (input2 == 3) {
                cout << "Enter the required leggings's name or ID, or type 'clear' to clear: ";
                cin.ignore();
                getline(std::cin, input3);
                if (input3 == "clear") {
                    cout << "Required leggings cleared.\n";
                    requiredLeggings = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
                }
                else {
                    for (Armor* leggings : leggingsCatalogue) {
                        search = leggings->getName();
                        search2 = leggings->getID();
                        if (search.find(input3) != string::npos || search2.find(input3) != string::npos)
                        {
                            requiredLeggings = leggings;
                            input2 = 0;
                            break;
                        }
                    }
                    if (input2 == 0)
                        cout << "Required leggings set to " << requiredLeggings->getName() << ".\n";
                    else
                        cout << "Leggings not found.\n";
                }
                cout << "Press any key to continue...";
                _getch();
            }
            else if (input2 == 4) {
                cout << "Enter the required boots's name or ID, or type 'clear' to clear: ";
                cin.ignore();
                getline(std::cin, input3);
                if (input3 == "clear") {
                    cout << "Required boots cleared.\n";
                    requiredBoots = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
                }
                else {
                    for (Armor* boots : bootsCatalogue) {
                        search = boots->getName();
                        search2 = boots->getID();
                        if (search.find(input3) != string::npos || search2.find(input3) != string::npos)
                        {
                            requiredBoots = boots;
                            input2 = 0;
                            break;
                        }
                    }
                    if (input2 == 0)
                        cout << "Required boots set to " << requiredBoots->getName() << ".\n";
                    else
                        cout << "Boots not found.\n";
                }
                cout << "Press any key to continue...";
                _getch();
            }
        }
        else if (input == 4) {
            optimalSets = findOptimalSets(optimize, helmCatalogue, chestplateCatalogue, leggingsCatalogue, bootsCatalogue, requiredHelm, requiredChestplate, requiredLeggings, requiredBoots, minimumValues);
            displaySets(optimalSets);
            cout << "Press any key to continue...";
            _getch();
        }
        else if (input == 5) {
            minimumValues = { "X", "X", "X", "X", "X", "X", "X", "X" };
            optimize = "Physical";
            requiredHelm = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
            requiredChestplate = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
            requiredLeggings = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
            requiredBoots = new Armor(-100, -100, -100, -100, -100, -100, -100, -100, "N/A", "N/A");
            cout << "All settings cleared. Press any key to continue...";
            _getch();
        }
    } while (input != 6);


    return 0;
}
