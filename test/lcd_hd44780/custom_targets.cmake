# PROJECT CUSTOM TARGETS FILE
#  here you can define custom targets for the project so all team member can use it in the same way
#  some example of custo targets are shown bello those are targets for:
# 		1. Running unit tests
# 		2. Code Complexity Metrics
# 		3. CppCheck static analize of specific folder
# 		4. Code Coverage report generation.


#TARGETS FOR RUNNING UNIT TESTS
message(STATUS "To run Unit Tests, you can use predefine target: \r\n\trun,")
add_custom_target(run lcd_hd44780_test)

# TARGET FOR CHECKING CODE COMPLEXITY METRICS"
# check if lizard software is available 
find_program(lizard_program lizard)
if(lizard_program)
	message(STATUS "Lizard was found, you can use predefined targets for src folder Code Complexity Metrics: \r\n\tccm,\r\n\tccmr,")
else()
	message(STATUS "Lizard was not found. \r\n\tInstall Lizard to get predefined targets for src folder Code Complexity Metrics")
endif()
# Prints CCM for src folder in the console
add_custom_target(ccm lizard 
						../../../src/ 
						--CCN 12 -Tnloc=30 
						-a 4 
						--languages cpp 
						-V 
						-i 1)
# Create CCM report in reports/Cylcomatic_Complexity/
# Tworzenie katalogu przed uruchomieniem lizard
add_custom_command(
    OUTPUT ../../../reports/CCM/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCM/
    COMMENT "Tworzenie katalogu raportów"
)
# Uruchomienie lizard po utworzeniu katalogu
add_custom_target(ccmr
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCM/
    COMMAND lizard 
        ../../../src/ 
        --CCN 12 
        -Tnloc=30 
        -a 4 
        --languages cpp 
        -V 
        -o ../../../reports/CCM/lcd_hd44780.html
    DEPENDS ../../../reports/CCM/
    COMMENT "Analiza kodu narzędziem Lizard"
)

# TARGET FOR MAKING STATIC ANALYSIS OF THE SOURCE CODE AND UNIT TEST CODE
# check if cppchec software is available 
find_program(cppcheck_program cppcheck)
if(cppcheck_program)
	message(STATUS "CppCheck was found, you can use predefined targets for static analize : \r\n\tcppcheck")
else()
	message(STATUS "CppCheck was not found. \r\n\tInstall CppCheck to get predefined targets for static analize")
endif()
# # Prints static analize output for src folder in the console
add_custom_target(cppcheck cppcheck
					../../../src
					../../../test/lcd_hd44780
					-i../../../test/lcd_hd44780/out
					--enable=all
					--force
					# --inconclusive
					--std=c99
					# --inline-suppr 
					# --platform=win64 
					--suppress=missingIncludeSystem 
					--suppress=missingInclude
					# --suppress=unusedFunction:../../../test/lcd_hd44780/lcd_hd44780_test_runner.c:3
					--checkers-report=cppcheck_checkers_report.txt
					)

# TARGET FOR CREATING CODE COVERAGE REPORTS
# check if python 3 and gcovr are available 
find_program(GCOVR gcovr)
find_program(PYTHON python)
if(PYTHON)
	if(GCOVR)
		message(STATUS "python 3 and gcovr was found, you can use predefined targets for uint tests code coverage report generation : \r\n\tccc, \r\n\tccr")
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
add_custom_command(
    OUTPUT ../../../reports/CCR/ ../../../reports/CCR/JSON_ALL/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/JSON_ALL/
    COMMENT "Tworzenie katalogów raportów Code Coverage"
)
add_custom_target(ccr 
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/JSON_ALL/
	COMMAND gcovr 
						-r ../../../src 
						--json ../../../reports/CCR/JSON_ALL/coverage_lcd_hd44780.json
						--json-base  src/
						--html-details ../../../reports/CCR/lcd_hd44780_report.html 
						.)
add_custom_target(ccc gcovr  
						-r ../../../src 
						--fail-under-line 90
						.)
