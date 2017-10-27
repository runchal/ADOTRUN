from random import choice as c
#
#
#
# a="?.!*%"
# v=">+-&"
# n="$#@"
# def p():
#     for x in range(randint(1,3)):
#         s=" "
#         s=r(n)+s+r(a)+r(v)+s+r(n)+"\n"
#         if x%2==0:
#             print s
#             print s
#         else:
#             print s
# p()

def s():
    return c("$#@")+" "+c("?.!*%")+c("?+-&")+" "+c("$#@")+ "\n"
def p():
    result = ""
    for a in range(c([1,3,7,11])):
        result += s()
    return result
print p()
