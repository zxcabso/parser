#include <iostream>
#include "parse.h"

int main()
{

	// csv files

    std::string inputFile = "a.csv";

    std::vector<parse::Csv::Row> rows = parse::Csv::readCsv(inputFile);

    parse::Csv::printCSV(rows);

    parse::Csv::searchCSV(rows,"Alex");



    // txt files

    std::vector<std::string> lines = parse::Txt::readTXT("a.txt");

    parse::Txt::printTXT(lines);

    parse::Txt::searchTXT(lines,"John");

    // xml files ( test ) 

    std::ifstream file("a.xml");
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 1;
    }

    parse::xml::xml root = parse::xml::parseXML(file);
    parse::xml::printXML(root,0);

    file.close();

    // html

    std::ifstream hfile("a.html");
    if (!hfile.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }

    parse::html::htmlNode hroot = parse::html::parseHTML(hfile);
    parse::html::printHTML(hroot);

    return 0;
}