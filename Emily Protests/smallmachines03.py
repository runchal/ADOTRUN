from __future__ import unicode_literals
from random import random
import spacy
nlp = spacy.load('en')

# file = open("emilywords2.txt","w")
doc = nlp(open("emilywords2.txt").read().decode('utf-8'))
# for item in doc.ents:
#     print item.text, item.label_

protest_word_actions = "no, not, for, stop"
protest_word_objects = "my, our, us, we're"

nouns = []
for item in doc:
    if item.pos_ == 'NOUN':
        nouns.append(item.text)

print random.choice(nouns)
