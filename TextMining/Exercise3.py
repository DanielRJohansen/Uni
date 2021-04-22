import os
import gzip
from xml.dom import minidom
from bs4 import BeautifulSoup as bs
import lxml

def getData(folder):
    folder = folder + "\\per_day"
    for date in os.listdir(folder):
        path = folder + '\\' + date
        f = gzip.open(path, 'rb')
        content = f.read()
        return content


def loadNXML(path):
    file = path + '\\' + os.listdir(path)[0]
    with open(file, 'r') as f:
        content = f.readlines()
        content = "".join(content)
        soup = bs(content, 'lxml')
        text = soup.findAll('p')
        print(text)
        ref = soup.find("ref id=\"bib23\"")
        print(ref)
        print(soup)


    return

    doc = minidom.parse(file)
    article = doc.getElementsByTagName('article')[0].childNodes[2].getElementsByTagName('p')[0].childNodes[2].nodeValue
    #print(article)







def Ex3():
    s1 = "D:\TextMining\\release\msnbc.com"
    data = getData(s1)

    s2 = "D:\TextMining\PMC5534960"
    loadNXML(s2)
