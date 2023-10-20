#!/bin/bash
#
# Tests for 1. IZP project [2023]
# Author: _ramb0_
# Usage:
#     ./test_keyfilter.sh


# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Compile the program
gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter

run_test() {
	input_file=$1
	test_arg=$2
	expected_output=$3

	echo -n "Running test with input from $input_file and argument ${test_arg:0:10}... "

		actual_output=$(./keyfilter "$test_arg" < "$input_file")

		if [[ "$actual_output" == "$expected_output" ]]; then
			echo -e "${GREEN}PASSED${NC}"
		else
			echo -e "${RED}FAILED${NC}"
			echo "Expected: $expected_output"
			echo "Got:      $actual_output"
		fi
	}

# Test cases
echo -e "Praha\nBrno\nBruntal\nBratislava" > test_01.txt

run_test "test_01.txt" "" "Enable: BP"

run_test "test_01.txt" "b" "Enable: R"
run_test "test_01.txt" "B" "Enable: R"

run_test "test_01.txt" "br" "Enable: ANU"
run_test "test_01.txt" "BR" "Enable: ANU"

run_test "test_01.txt" "brn" "Found: BRNO"
run_test "test_01.txt" "BRN" "Found: BRNO"

run_test "test_01.txt" "be" "Not found"
run_test "test_01.txt" "BE" "Not found"

# More complex file
echo -e "Praha\nBrno\nBruntal\nBratislava\nBerlin\nBudapest\nPrague\nBrunswick\nBritain\nBrazil\nBremen" > test_02.txt

run_test "test_02.txt" "" "Enable: BP"

run_test "test_02.txt" "b" "Enable: ERU"

run_test "test_02.txt" "br" "Enable: AEINU"
run_test "test_02.txt" "BR" "Enable: AEINU"

run_test "test_02.txt" "bru" "Enable: N"
run_test "test_02.txt" "BRU" "Enable: N"

run_test "test_02.txt" "brun" "Enable: ST"

run_test "test_02.txt" "brunt" "Found: BRUNTAL"

run_test "test_02.txt" "be" "Found: BERLIN"

run_test "test_02.txt" "ber" "Found: BERLIN"

run_test "test_02.txt" "berl" "Found: BERLIN"

run_test "test_02.txt" "bremen" "Found: BREMEN"

run_test "test_02.txt" "p" "Enable: R"

run_test "test_02.txt" "TOHLEJETESTNASTOCHARAKTERUDLOUHEJRADEKJESTLINAHODOUJSITAMNEUDELALCHYBICKUFRAJEREJUSTASKINGYOUKNOWHEHaaaaaa" "100 characters is max!"

echo -e "TohleJeTestNaStoCharakteruDlouhejRadekJestliNahodouJsiTamNeudelalChybickuFrajereJustAskingYouKnowHeh" > test_03.txt
run_test "test_03.txt" "to" "Found: TOHLEJETESTNASTOCHARAKTERUDLOUHEJRADEKJESTLINAHODOUJSITAMNEUDELALCHYBICKUFRAJEREJUSTASKINGYOUKNOWHEH"

echo -e " \n1praha\n1kurim\n3\n!\n:\n_\n;\n~\nA\nB\nc" > test_04.txt

run_test "test_04.txt" "" "Enable:  !13:;ABC_~"
run_test "test_04.txt" "1" "Enable: KP"

#white spaces
echo -e " \nBratislava\nBrno hl.n.\nBrno hl.aut.n\nBrno\nBruntal" > test_05.txt

run_test "test_05.txt" "brno h" "Enable: L"
run_test "test_05.txt" "brno hl." "Enable: AN"

echo -e "TohleJeTestNaStoCharakteruDlouhejRadekJestliNahodouJsiTamNeudelalChybickuFrajereJustAskingYouKnowHehTesfdsfdsfdsfdsdsadsadsadsadsa\nPraha" > test_06.txt
run_test "test_06.txt" "to" "Max 100 characters per address!"

rm test_06.txt
rm test_05.txt
rm test_04.txt
rm test_03.txt
rm test_02.txt
rm test_01.txt
