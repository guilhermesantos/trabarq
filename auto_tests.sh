echo 'Fazendo testes de multiplicacao de matrizes inteiras'

PLAT_NAME=$1
for i in {1..10}
	do
		sudo perf stat ./bench_int_mat &>> result_int_mat_$PLAT_NAME.txt
	done

echo 'Fazendo testes de multiplicacao de matrizes float'
for i in {1..10} 
	do
		sudo perf stat ./bench_float_mat &>> result_float_mat_$PLAT_NAME.txt
	done

echo 'Fazendo testes de gauss'
for i in {1..10} 
	do
		sudo perf stat ./bench_float_gauss &>> result_float_gauss_$PLAT_NAME.txt
	done

echo 'Fazendo testes de branch sem sort'
for i in {1..10} 
	do
		sudo perf stat ./bench_branch &>> result_branch_$PLAT_NAME.txt
	done

echo 'Fazendo testes de branch com sort'
for i in {1..10} 
	do
		sudo perf stat ./bench_branch_sort &>> result_branch_sort_$PLAT_NAME.txt
	done