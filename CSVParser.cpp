#include "CSVParser.h"

#include <fstream>
#include <iostream>

CSVDataSet::CSVDataSet(std::vector<std::string> _columns)
    : columnNames(_columns){};

void CSVDataSet::insertRow(const std::vector<std::string> &values)
{
    if (values.size() != columnCount())
        return; // This row has the incorrect amount of columns and so is malformed

    std::vector<std::string> row;
    for (size_t i = 0; i < values.size(); i++)
    {
        row.push_back(values[i]);
    }
    rows.push_back(row);
};

inline std::size_t CSVDataSet::columnCount()
{
    return columnNames.size();
};

std::size_t CSVDataSet::rowCount()
{
    return rows.size();
};

float CSVDataSet::getColumnAverage(std::string columnName)
{
    size_t columnIndex;
    // Search for the index of the column
    size_t i{0};
    do
    {
        if (columnNames[i] == columnName)
        {
            columnIndex = i;
            break;
        }
        ++i;
    } while (i < columnNames.size());

    if (i == columnNames.size())
    {
        std::cout << "Column name could not be found" << std::endl;
        return 0;
    }

    float average{0};

    for (const std::vector<std::string> &row : rows)
    {
        try
        {
            average += std::stof(row[columnIndex]);
        }
        catch (const std::exception &e)
        {
            // Could not convert line to float
        }
    }

    return average / rows.size();
}

CSVDataSet CSVParser::parseCSV(std::string filePath)
{
    std::ifstream csvFile{filePath};

    if (!csvFile.is_open())
    {
        std::cout << "Unable to open " << filePath << std::endl;
        csvFile.close();
        throw std::invalid_argument("Could not load file");
    }

    std::cout << "Opened " << filePath << std::endl;

    std::string line;
    // Get the first line which should contain the column names
    std::getline(csvFile, line);
    std::vector<std::string> columns = tokenise(line, ',');

    CSVDataSet dataSet{columns};

    // Get the remaining lines and add them to the dataset
    while (std::getline(csvFile, line))
    {
        std::vector<std::string> tokens = tokenise(line, ',');
        dataSet.insertRow(tokens);
    }

    csvFile.close();
    return dataSet;
};

std::vector<std::string> CSVParser::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string token;

    signed int start, end;
    start = csvLine.find_first_not_of(separator);

    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;

        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1;
    } while (end != std::string::npos);

    return tokens;
}