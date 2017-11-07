import markovify
import re
import spacy
import shutil
import glob


nlp = spacy.load('en')

class POSifiedText(markovify.Text):
    def word_split(self, sentence):
        return ["::".join((word.orth_, word.pos_)) for word in nlp(sentence)]

    def word_join(self, words):
        print "workinggggg"
        sentence = " @@@ ".join(word.split("::")[0] for word in words)
        return sentence


outfilename = 'Data/all_manifestos.txt' #this  will create
                                        #a storage file for manifestos


#this function takes all the files in a folder and creates a new file
#not sure if it overrides itself
with open(outfilename, 'wb') as outfile:
    for filename in glob.glob('Data/*.txt'):
        if filename == outfilename: #makes sure not to copy the outfile into itself
            continue
        with open(filename, 'rb') as readfile:
            shutil.copyfileobj(readfile, outfile)





#STARTING TO USE SPACY TO IMPROVE RESULTS
##NOT WORKING YET
#### BASIC MARKOV CHAIN TO BUILD FIVE SENTENCES
text = open(outfilename, 'r').read()

text_model = markovify.Text(text)

text_output =open("test.txt", 'w')


for i in range(3):
    print(text_model.make_short_sentence(140))

# mprint = print(text_model.make_sentence())


# def man_return():
#     return text_model.make_sentence()
#
# def write_output(data):
#     file_name = r'test.txt'
#     with open(file_name, 'wb') as x_file:
#         x_file.write('{}')


# for i in range(3):
#     text_output.write(text_model.make_sentence().print)

#PRINT A FEW THINGS

## THIS WILL PRINT THINGS
# for i in range(5):
#     print(text_model.make_sentence())

man_list = []

def m_writer(n = 5):
    for i in range(n):
        man_list.append(text_model.make_sentence())

m_writer()

# print man_list

# with open("test.txt", "w") as text_file:
#     text_file.write("testing")
# text_file.close()



# file.open('exported.txt', 'w').write()
#
# def m_m():
#     return text_model.make_sentence()
#
# mprint = m_m()
#
# print text_model.make_sentence()


# for i in range(3000):
#     print text_model.make_sentence()

#
# output = printer()
#
# with open('exported.txt', 'w') as file:
#     file.write(output)
