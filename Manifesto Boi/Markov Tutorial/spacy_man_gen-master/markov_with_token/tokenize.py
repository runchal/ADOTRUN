
from sys import argv
import re
from collections import Counter

script_filename, book_filename, order_str = argv

def tokenize_simple(text):
        return text.lower().split()

def tokenize_regex(text):
        return re.findall(r'\w+', text.lower())

def tokenize_nosplit(text):
  return re.findall(r'\b[\w\']+\b', text.lower())


if __name__ == '__main__':

  if len(argv) != 2:
    raise Exception('Script required')


script_filename, book_filename, order_str = argv

with open(book_filename, 'r') as infile:

  file_text = infile.read()

simple_tokens = tokenize_simple(file_text)

simple_token_counter = Counter(simple_tokens)

print(simple_token_counter.most_common())

regex_tokens = tokenize_regex(file_text)

regex_token_counter = Counter(regex_tokens)

print(regex_token_counter.most_common())
