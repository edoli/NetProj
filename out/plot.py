from Tkinter import *

w = 1536
h = 512

def cc(test_name, cv, x, y):
	cv.create_rectangle((1,1,512,512))

	def client(x, y):
		x = (x * w) / 100
		y = (y * h) / 100
		cv.create_oval((x,y,x+5,y+5),fill="#e74c3c")

	def wifi(x, y):
		x = (x * w) / 100
		y = (y * h) / 100
		cv.create_oval((x,y,x+5,y+5),fill="#3498db")

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

cv = Canvas(root, bg="white", width=w, height=h)


cc('normal', cv, 0, 0)
cc('kmean', cv, 512, 0)
cc('gravity', cv, 1024, 0)

#root.title('%s' % (test_name))
root.resizable(width=FALSE, height=FALSE)
root.geometry('{}x{}'.format(w + 12, h + 4))
root.mainloop()


