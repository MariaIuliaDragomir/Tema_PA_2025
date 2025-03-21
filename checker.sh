#!/bin/bash

# Exec name
EXEC_NAME=main

NUM_TESTS=7
POINTS_TEST=(
    20
    10
    10
    20
    10
    10
    30
)

points=0

function compare_files {
	flag_diff=0
    diff -Z -q $1 $2 > /dev/null 2>&1
	if [ $? -eq 0 ];
	then
		flag_diff=1
	else
		flag_diff=0
	fi
}

function add_points {
    if [ "$flag_diff" -eq 1 ]; then
        printf "Test %2d ................................. (+%2dpt)\n" $(($1 + 1)) $((POINTS_TEST[$1]))
        (( points += POINTS_TEST[$1] ))
    else
        printf "Test %2d ................................. (+%2dpt)\n" $(($1 + 1)) $((0))
    fi
}

rm -f "Pas_1/test_1.csv"
rm -f "Pas_2/test_2_lorzi.csv"
rm -f "Pas_2/test_2_cavaleri_aventurieri.csv"
rm -f "Pas_3/test_3_lorzi.csv"
rm -f "Pas_4/test_4.csv"
rm -f "Pas_5/test_5.csv"
rm -f "Pas_6/test_6.csv"
rm -f "Pas_7/test_7.csv"
rm -f "./Upload_Tema_Moodle"

make clean # Clean
make       # Build
# Run to write the output (directly with Valgrind)
valgrind --leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
--verbose \
--log-file=valgrind-out.txt \
--error-exitcode=1 \
./main
valgrind_exit_code=$?

compare_files "Pas_1/test_1.csv" "Pas_1/ref_test_1.csv"
add_points 0

compare_files "Pas_2/test_2_lorzi.csv" "Pas_2/ref_test_2_lorzi.csv"
aux_flag_diff=$flag_diff
compare_files "Pas_2/test_2_cavaleri_aventurieri.csv" "Pas_2/ref_test_2_cavaleri_aventurieri.csv"

flag_diff=$((aux_flag_diff && flag_diff))
add_points 1

compare_files "Pas_3/test_3_lorzi.csv" "Pas_3/ref_test_3_lorzi.csv"
add_points 2

compare_files "Pas_4/test_4.csv" "Pas_4/ref_test_4.csv"
add_points 3

compare_files "Pas_5/test_5.csv" "Pas_5/ref_test_5.csv"
add_points 4

compare_files "Pas_6/test_6.csv" "Pas_6/ref_test_6.csv"
add_points 5

compare_files "Pas_7/test_7.csv" "Pas_7/ref_test_7.csv"
add_points 6

if [ "$points" -ge 10 ]; then
	if [ "$valgrind_exit_code" -eq 1 ]; then
		echo "S-au detectat scurgeri de memorie, veți fi depunctat 10 puncte!"
		points=$(($points-10))
	else
		echo "Nu s-au detectat scurgeri de memorie, NU veți fi depunctat."
	fi
fi

# printf "NOTA FINALA ..................................... %3spt\n" $(($points))
# echo

echo -e "Observatie: 20pt vor fi adaugate ulterior pentru soft deadline (10pt) si documentatie (10pt)"
echo -e "\nTotal: $points/130pt"
echo



zip -r Upload_Tema_Moodle.zip * >/dev/null && echo "Arhivat cu succes!" || echo "Arhivarea a esuat!"
echo



