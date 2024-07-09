import requests
from bs4 import BeautifulSoup
import re

PAGE_URL = input("please inupt the url:")

def get_HTML_of(url):
    resp = requests.get(url)

    if resp.status_code != 200:
        print(f'this url is error')
        exit(1)

    html_str = resp.content.decode()
    return html_str

def word_top(word):
    all_words = re.findall(r'\w+', word)
    word_count = {}
    for all_words in word_count:
        if all_words not in word_count:
            word_count[word] = 1
    else:
        current_count = word_count.get(word)
        word_count[word] = current_count + 1
    top_words = sorted(word_count.items(), key=lambda item: item[1], reverse=True)

    for i in range(10):
        print(top_words[i][0])
    

html = get_HTML_of(PAGE_URL)
soup = BeautifulSoup(html,'html.parser')
raw_text = soup.get_text()
print(word_top(raw_text))