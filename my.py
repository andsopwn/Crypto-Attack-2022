import os
import re as cut
import requests
from bs4 import BeautifulSoup as bus
from tkinter import *
from tkinter import messagebox

def connect():
    print("HELLO")

def no():
    exit()

def refresh():
    news.clear()
    date.clear()
    url = requests.get('https://sejong.korea.ac.kr/campuslife/notice/scholarship')
    data = bus(url.text, 'html.parser')
    content = data.find('div', {'class':'list02'}).find('ul').find_all('li')
    for i in range(5):
        news.append(content[i].find('p').text.strip())
        #date_aa = content[i].find_all('dd')
        #date_aa = date_aa[1]
        #date.append(date_aa.text.strip())
        
news = []
date = []

refresh()
#print(news[0])
#print(date[0])

window = Tk()
    
#Click(news)
window.title("🐯 고려대학교 장학금 공지사항 알리미 🐯")
window.geometry("600x300+300+300")
window.resizable(False, False)

label_info = Label(window, text = "장학금 정보를 가져옵니다.", borderwidth=15)
label = Label(window, text=news[0])
b1 = Button(window, text = '바로가기', command=connect)
b2 = Button(window, text = '새로고침', command=refresh)
label_info.pack()
label_info.configure(font=("Courier",'20',"bold"))
label.pack()

b1.flash()
b2.flash()
b1.pack()
b2.pack()
window.mainloop()


