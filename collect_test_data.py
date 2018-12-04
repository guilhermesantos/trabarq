import sys

def process_clock(line):
	time = float(line.split()[0].replace(',','.'))
	#print('time ',time)
	return time

def process_icp(line):
	icp = float(line.split('#')[1].split()[0].replace(',','.'))
	#print('icp',icp)
	return icp

def process_branch(line):
	branch_misses =  int(line.split('#')[0].split()[0].replace('.',''))
	#print(branch_misses)
	return branch_misses

def process_cache(line):
	cache_misses = int(line.split('#')[0].split()[0].replace('.','') )
	#print('cache_misses', cache_misses)
	return cache_misses

def collect_data():
	file_name = sys.argv[1]
	plats = ['i5']
	tests = ['int_mat','float_mat','float_gauss','dep','branch','branch_sort']
	for plat in plats:
		for test in tests:
			print('result_{}_{}'.format(test,plat))

	results = dict()
	for plat in plats:
		for test in tests:
			test_name = '{}_{}'.format(test,plat)
			file_name = 'result_{}.txt'.format(test_name)

			content = []
			with open(file_name,'r') as f:
				content = f.readlines()
				#print(content)

			content = [x.strip() for x in content]
			#print(content)

			i = -1
			results[test_name] = dict()
			for line in content:
				if('task-clock' in line):
					i += 1
					results[test_name]['clock'] = process_clock(line)
				if('instructions' in line):
					results[test_name]['icp'] = process_icp(line)
				if('branch-misses' in line):
					results[test_name]['branch_misses'] = process_branch(line)
				if('L1-dcache-load-misses' in line):
					results[test_name]['cache_misses'] = process_cache(line)
			print('resultado do teste {}'.format(test_name))
			print(results[test_name])


	print(results)
	return results

collect_data()