#pragma once

#include <string>
#include <optional>

class NewSpreadsheetCell {
public:

    virtual void set(std::string value) = 0;

    virtual std::string getString() const = 0;

    virtual ~NewSpreadsheetCell() = default;
};

class DoubleSpreadsheetCell : public NewSpreadsheetCell {
public:
    void set(std::string value) override;

    void set(double value);

    std::string getString() const override;

private:
    std::optional<double> m_value;

    static std::string doubleTostring(double value);

    static double stringTodouble(std::string value);
};

class StringSpreadsheetCell : public NewSpreadsheetCell {
public:
    StringSpreadsheetCell() = default;

    StringSpreadsheetCell(const DoubleSpreadsheetCell &cell) : m_value{cell.getString()} {};

    void set(std::string value) override;

    std::string getString() const override;

private:
    std::optional<std::string> m_value;
};
