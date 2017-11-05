import re

# re.match(pattern, string, flags=0)

line = "Cats are smarter than dogs"

matchObj = re.match( r'(.*) are (.*?) .*', line, re.M|re.I)

if matchObj:
   print "matchObj.group() : ", matchObj.group()
   print "matchObj.group(1) : ", matchObj.group(1)
   print "matchObj.group(2) : ", matchObj.group(2)
else:
   print "No match!!"



text = " XF is not a bid for revolution, but a wager on the long game of history, demanding imagination, dexterity and persistence. "


matchRe = re.match(r'(\s*(,\d{3})\s*), text)


# line.partition(keyword)