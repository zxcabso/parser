#include <iostream>
#include "parse.h"

int main()
{

	// csv files

    std::string inputFile = "a.csv"; // our File

    std::vector<parse::Csv::Row> rows = parse::Csv::readCsv(inputFile); // read our Csv file

    // Print csv

    parse::Csv::printCSV(rows);
    
    // easily find smth in CSV

    parse::Csv::searchCSV(rows,"Alex");
}