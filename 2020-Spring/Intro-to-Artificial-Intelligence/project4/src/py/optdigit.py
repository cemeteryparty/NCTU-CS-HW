from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
import numpy as np
import pandas as pd
import sys

def main():
	digits_train = pd.read_csv('optdigits\\optdigits.tra', header = None)
	digits_test = pd.read_csv('optdigits\\optdigits.tes', header = None)
	train_x,train_y = digits_train[np.arange(64)],digits_train[64] # digit picture,digit
	test_x,test_y = digits_test[np.arange(64)],digits_test[64] # digit picture,digit
	
	tree = DecisionTreeClassifier(criterion = 'gini', max_depth = 15, random_state = 0)
	tree.fit(train_x,train_y)
	res_y = tree.predict(test_x)
	"""
	forest = RandomForestClassifier(criterion = 'gini', n_estimators = 10, random_state = 3)
	forest.fit(train_x,train_y)
	res_y = forest.predict(test_x)
	"""
	count = 0
	for i in range(0,len(res_y)):
		print('res = ',res_y[i])
		print('ans = ',test_y[i])
		if res_y[i] == test_y[i]:
			count += 1
			print('Correct')
		else:
			print('Wrong')
		print('----------------')
	print('{0:d} / {1:d} = {2:.2f}'.format(count,len(res_y),count / len(res_y)))
if __name__ == '__main__':
	main()