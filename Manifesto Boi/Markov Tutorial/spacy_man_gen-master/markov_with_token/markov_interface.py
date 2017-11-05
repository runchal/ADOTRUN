
from collections import defaultdict
from collections import Counter
from random import choice
import json

def make_model(tokens, order):
        model = defaultdict(Counter)
        for i in range(len(tokens)-order):
                history = tuple(tokens[i:i+order])
                next_token = tokens[i+order]
                model[history][next_token] += 1

        def order(counter):
                return sorted(list(counter.keys()), key=lambda t: counter[t])

        final_model = {hist:order(token_counter) for hist, token_counter in model.items()}
        return final_model

def generate(model, length, seed=False):
        if not seed:
                seed = choice(list(model.keys()))
        elif not seed in model:
                raise Exception("Seed not in model!")

        result = list(seed)

        def generate_token(history):
                candidates = model[history]
                if len(candidates) > 1:
                        i = 1
                        for c in candidates:
                                print('%i. %s' % (i,c))
                                i = i+1
                        user_input = input('> ')
                        choice_ix = int(user_input) - 1
                        return candidates[choice_ix]
                else:
                        return candidates[0]

        for i in range(length):
                print('\n')
                print(' '.join(result))
                next_token = generate_token(seed)
                result.append(next_token)
                prior_tokens = list(seed)[1:]
                prior_tokens.append(next_token)
                seed = tuple(prior_tokens)

        return ' '.join(result)

if __name__ == '__main__':
        from sys import argv
        from tokenize import tokenize_nosplit

        if len(argv) != 3:
                raise Exception('Script requires a file to and an order.')

        script_filename, book_filename, order_str = argv

        # with open(book_filename, 'r', encoding='latin-1', errors='ignore') as infile:
        with open(book_filename, 'r') as infile:
                book_text = infile.read()

        book_tokens = tokenize_nosplit(book_text)

        book_model = make_model(book_tokens, int(order_str))

        print(generate(book_model, 100))
