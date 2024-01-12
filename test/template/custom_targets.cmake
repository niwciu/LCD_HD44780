# PROJECT CUSTOM TARGETS FILE
#  here you can define custom targets for the project so all team member can use it in the same way
#  some example of custo targets are shown bello those are targets for:
# 		1. Code Complexity Metrics
# 		2. CppCheck static analize of specific folder
# 		3. Code Coverage report generation.

#TARGETS FOR RUNNING UNIT TESTS
add_custom_target(run template_test)

# TARGET FOR CHECKING CODE COMPLEXITY METRICS"
# check if lizard software is available 
find_program(lizard_program lizard)
if(lizard_program)
	message(STATUS "Lizard was found, you can use predefined targets for src folder Code Complexity Metrics: \r\n\tccm,\r\n\ttccmr")
else()
	message(STATUS "Lizard was not found. \r\n\tInstall Lizard to get predefined targets for src folder Code Complexity Metrics")
endif()
# Prints CCM for src folder in the console
add_custom_target(ccm lizard src/ --CCN 12 -Tnloc=30 -a 4 --languages cpp -V -i 1)
# Create CCM report in reports/Cylcomatic_Complexity/
add_custom_target(ccmr lizard src/ --CCN 12 -Tnloc=30 -a 4 --languages cpp -V -o ../../../reports/Cyclomatic_Complexity/Lizard_report.html)

# TARGET FOR MAKING STATIC ANALYSIS OF THE SOURCE CODE AND UNIT TEST CODE
# check if cppchec software is available 
find_program(cppcheck_program cppcheck)
if(cppcheck_program)
	message(STATUS "CppCheck was found, you can use predefined targets for static analize : \r\n\tcppcheck_src,\r\n\tcppcheck_tests.")
else()
	message(STATUS "CppCheck was not found. \r\n\tInstall CppCheck to get predefined targets for static analize")
endif()
# Prints static analize output for src folder in the console
add_custom_target(cppcheck_src cppcheck ../../../src --enable=all --inconclusive --force --inline-suppr --platform=win64 --suppress=missingInclude --suppress=missingIncludeSystem) #--suppress=unusedFunction) # -> last argument usefull for libraries
# Prints static analize output for specific test_module folder in the console -> example neeed to modify in project
# add_custom_target(cppcheck_test cppcheck ../../../test/lcd_hd44780 -itest/lcd_hd44780/out -itest/lcd_hd44780/out_avr --enable=all --inconclusive --force --inline-suppr --platform=win64 --suppress=missingInclude --suppress=missingIncludeSystem)
add_custom_target(cppcheck_tests echo  The target definition is not completed. Complete the target definition in the file custom_targets.cmake )

# TARGET FOR CREATING CODE COVERAGE REPORTS
# check if python 3 and gcovr are available 
find_program(GCOVR gcovr)
find_program(PYTHON3 python3)
if(PYTHON3)
	if(GCOVR)
		message(STATUS "python 3 and gcovr was found, you can use predefined targets for uint tests code coverage report generation : \r\n\tccr")
	else()
		message(STATUS "pyton 3 was found but gcovr was not found. \r\n\tInstall gcovr to get predefined targets for uint tests code coverage report generation")
	endif()
else()
	if(GCOVR)
		message(STATUS "python3 was not found. \r\n\tInstall python 3 to get predefined targets for uint tests code coverage report generation")
	else()
		message(STATUS "python3 and gcovr were not found. \r\n\tInstall python 3 and gcovr to get predefined targets for uint tests code coverage report generation")
	endif()
endif()
# Create Code Coverage report in reports/Code_Coverage/lcd_hd44780_gcov_report.html -> path for gcovr input need to be modified!!! bellow it's only a example of some target from som project
# add_custom_target(ccr python3 -m gcovr CMakeFiles/lcd_hd44780_test.dir/D_/0_Projekty/6_Biblioteki/LCD_HD44780/src -r ../../.. --html-details ../../../reports/Code_Coverage/lcd_hd44780_gcov_report.html)
add_custom_target(ccr echo  The target definition is not completed. Complete the target definition in the file custom_targets.cmake )