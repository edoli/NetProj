from Tkinter import *

w = 512
h = 512

def cc(test_name, cv, cx, cy):
	cv.create_rectangle((cx + 1, cy + 1,cx + 512, cy + 512))

	def client(x, y):
		x = cx + (x * w) / 100
		y = cy + (y * h) / 100
		cv.create_oval((x-3,y-3,x+3,y+3),fill="#e74c3c")

	def wifi(x, y):
		x = cx + (x * w) / 100
		y = cy + (y * h) / 100
		cv.create_oval((x-5,y-5,x+5,y+5),fill="#3498db")

	f = open('%s_test.txt' % (test_name))
	data = f.read().split('-----')
	f.close()

	wifi_data = data[0]
	client_data = data[1]

	for row in wifi_data.strip().split('\n'):
		pt = row.split(',')
		wifi(float(pt[0]), float(pt[1]))


	for row in client_data.strip().split('\n'):
		pt = row.split(',')
		client(float(pt[0]), float(pt[1]))


	cv.pack()

root = Tk()

cv = Canvas(root, bg="white", width=w*3, height=h)


cc('kmean', cv, 0, 0)
cc('kmean Random', cv, 512, 0)
cc('kmean Penalty', cv, 1024, 0)

#root.title('%s' % (test_name))
root.resizable(width=FALSE, height=FALSE)
root.geometry('{}x{}'.format(w*3 + 12, h + 4))
root.mainloop()


