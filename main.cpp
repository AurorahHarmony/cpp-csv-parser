#include "CSVParser.h"

#include <iostream>

int main()
{
    CSVDataSet dataSet{CSVParser::parseCSV("horse.csv")};

    std::cout << "Row count is: " << dataSet.rowCount() << std::endl;

    float averagePulse{dataSet.getColumnAverage("\"pulse\"")};
    std::cout << "Average pulse: " << averagePulse << std::endl;

    return 0;
}