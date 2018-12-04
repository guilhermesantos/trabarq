echo 'Fazendo testes de multiplicacao de matrizes inteiras'

for i in {1..10}
	do
		sudo perf stat ./bench_int_mat &>> result_int_mat_i5.txt
	done

echo 'Fazendo testes de multiplicacao de matrizes float'
for i in {1..10} 
	do
		sudo perf stat ./bench_float_mat &>> result_float_mat_i5.txt
	done

echo 'Fazendo testes de multiplicacao de gauss'
for i in {1..10} 
	do
		sudo perf stat ./bench_float_gauss &>> result_float_gauss_i5.txt
	done

echo 'Fazendo testes de multiplicacao de branch (sem sort)'
for i in {1..10} 
	do
		sudo perf stat ./result_branch_i5 &>> result_branch_i5.txt
	done

echo 'Fazendo testes de multiplicacao de branch (com sort)'
for i in {1..10} 
	do
		sudo perf stat ./result_branch_sort_i5 &>> result_branch_i5.txt
	done