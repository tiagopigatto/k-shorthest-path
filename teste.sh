#1/bin/bash

#Uso: ./teste.sh > teste.log 2>&1

for i in {1..18}
do
	for j in {1..18}
	do
		echo "Teste $(((($i-1)*18)+$j))"
		echo "Origem: 	[$i]"
		echo "Destino:	[$j]"
		./k-shorthest-path $i $j 3
		echo ""
		echo ""
	done
done
