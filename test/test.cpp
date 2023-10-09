#include "gtest/gtest.h"
#include <vector>
#include "../src/Spreadsheet.hpp"
#include "../src/SpreadsheetCell.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(EXAMPLE, random_test) {
    ASSERT_EQ(1, 1);
}

TEST(EXAMPLE, test_spreadsheet) {
    Spreadsheet sheet1{3,3};
    SpreadsheetCell cell1 {1};
    sheet1.setCellAt(1,1,cell1);
    SpreadsheetCell cell2 {sheet1.getCellAt(1,1)};
    ASSERT_EQ(cell2.getValue(), cell1.getValue());
}