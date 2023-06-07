#pragma once

#include <string>
#include <vector>

class CSVDataSet
{
public:
    CSVDataSet(std::vector<std::string> columns);

    void insertRow(const std::vector<std::string> &values);

    std::size_t columnCount();
    std::size_t rowCount();

    /** Calculates the mean average of all values in a column*/
    float getColumnAverage(std::string columnName);

private:
    std::vector<std::string> columnNames;
    std::vector<std::vector<std::string>> rows;
};

class CSVParser
{
    CSVParser() = delete;

public:
    /**
     * Loads and parses a CSV from the specified filepath. dataSet is an outparam which will store the parsed data.
     * Returns 0 on success
     * Returns 1 on error
     */
    static CSVDataSet parseCSV(std::string filePath);

private:
    /** Separates a string into tokens*/
    static std::vector<std::string> tokenise(std::string csvLine, char separator);
};
