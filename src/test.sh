#!/bin/bash

FILE=$1
DIR=$2

for f in "${DIR}"/*.in
do
	touch "${DIR}"/temp.out
	touch "${DIR}"/temp.err
	OUT="${DIR}"/temp.out
	ERR="${DIR}"/temp.err
	valgrind --error-exitcode=2137 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -q ./"$FILE" <"$f" >"$OUT" 2>"$ERR"
	VALGRIND=$?
	if [ $VALGRIND -eq 2137 ]
	then 
		echo "Memory Leak"
	else
		echo Przetwarzam: "Plik $f "
		if cmp -s "${f%in}out" "$OUT"
		then 
			if cmp -s "${f%in}err" "$ERR"
			then
				echo "Out and Err $f is OK"
			else
				echo "Err $f is NOT_OK"
			fi
		else
			echo "Test $f is NOT_OK"
		fi
	fi
done

