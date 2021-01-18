import sys
while True:
	strr = sys.stdin.readline().strip().replace('\x1a','')
	if strr == '':
		break
	arr = strr.split(' ')
	ans = 0
	for i in arr:
		if i != '':
			ans += int(i)
	print(ans)
