#include <iostream>
#include <xlnt/xlnt.hpp>

int main() {
	xlnt::workbook wb;
	wb.load("../tests/workbook.xlsx");
	auto sheet = wb.active_sheet();
	
	for (auto row : sheet.rows(false)) {
		for (auto cell : row) {
			std::cout << cell.to_string() << std::endl;
		}
		std::cout << "=========End of row===============" << std::endl;
	}
	
	return 0;
}
