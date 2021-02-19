from sklearn.ensemble import RandomForestClassifier
import numpy as np
import pandas as pd
import sys

def read_data(filename):
	pictures,values = [],[]
	picture = []
	f = open(filename, 'r')
	for line in f:
		line = line.strip()
		if len(line) == 32:
			for pixel in line:
				picture.append(pixel)
		elif len(line) == 1:
			pictures.append(picture)
			values.append(line)
			picture = []
	f.close()
	return pictures,values
def printpicture(picture):
	for i in range(0,32):
		print('   ',end = '',flush = True)
		for j in range(0,32):
			print(picture[i * 32 + j],end = '',flush = True)
		print()
def main():
	train_x,train_y = read_data('optdigits\\optdigits-orig.tra') # digit picture,value
	test_x,test_y = read_data('optdigits\\optdigits-orig.cv')
	"""
	class_distribution = [0] * 10
	for ty in train_y:
		class_distribution[ord(ty) - 48] += 1
	print(class_distribution)
	"""
	forest = RandomForestClassifier(criterion = 'gini', n_estimators = 10, random_state = 3)
	forest.fit(train_x,train_y)
	res_y = forest.predict(test_x)
	count = 0
	for i in range(0,len(res_y)):
		if res_y[i] == test_y[i]:
			count += 1
			print('--------------------------')
		else:
			print('Wrong\tres = {0},ans = {1}'.format(res_y[i],test_y[i]))
			printpicture(test_x[i])
	print('{0:d} / {1:d} = {2:.2f}'.format(count,len(res_y),count / len(res_y)))
if __name__ == '__main__':
	main()