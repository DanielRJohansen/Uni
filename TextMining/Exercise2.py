from bs4 import BeautifulSoup







def e1b(soup):
    links = []
    for link in soup.findAll('a'):
        links.append(link.get('href'))
    print(links)

def e1c(soup):
    paragraphs = []
    for paragraph in soup.findAll('p'):
        paragraphs.append(paragraph.getText().replace('\n',''))
    print(paragraphs)


def Ex2():
    with open("WSB.html", encoding="utf8") as fp:
        soup = BeautifulSoup(fp, "html.parser")

    e1b(soup)
    e1c(soup)