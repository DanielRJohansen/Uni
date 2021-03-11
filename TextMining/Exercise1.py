


def inSentence(word):
    legals = ["Mr.", "etc.", "Mrs."]
    for elem in legals:
        if word == elem:
            return True
    return False

def addSentence(sentence, sentences):
    if sentence != []:
        sentences.append(sentence)


def addWordToSentence(word, sentence):
    if word != "":
        sentence.append(word)

def sentensizeText(text):
    sentences = []
    sentence = []
    word = ""

    for i in range(len(text)):
        char = text[i]

        if char == '"':
            continue

        elif (char == " "):
            if word == "":
                continue
            addWordToSentence(word, sentence)
            word = ""

            if (sentence[-1][-1] == '.' and not inSentence(sentence[-1])) or sentence[-1][-1] == '!' or sentence[-1][-1] == '?':
                addSentence(sentence, sentences)
                sentence = []



        elif char == '\n':
            addWordToSentence(word, sentence)
            word = ""
            if sentence != []:
                if sentence[-1][-1] == '.' or sentence[-1][-1] == '?' or sentence[-1][-1] == '!':
                    addSentence(sentence, sentences)
                    sentence = []

        else:
            word = word+char
    for sentence in sentences:
        print(sentence)



def Ex1():
    f = open("PridePrejudiceSample", "r")
    text = f.read()
    sentensizeText(text)