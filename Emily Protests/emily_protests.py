
# coding: utf-8

# In[4]:


from random import choice


# In[8]:


first = ["Stop", "Oppose", "Support", "Arrested", "Strike", "Slips", "Arbitrate", "Perish"]
joiner = ["The", "--", "Some", "A", "All", "Minor", "", "Horrid", "Sleek"]
second = ["Troop", "Troops", "War", "Wars", "President", "Presidents", "Footmen", "Footman", "Marauder", "Marauders", "Abortion", "Abortions"]
splitter = ["", ",", "--", ';']
punct = [",", ".", "--", ";"]
endpunct = [".", "!", ""]
array_1 = ["-", "--"]
array_2 = [".", "..", "...", "...."]
join_array = [array_1,array_2]

for items in range(10):
    print(choice(choice(join_array)))

# In[10]:


# for items in range(25):
#     print ("------------" + "\n" + choice(first) + choice(splitter) + "\n" + choice(joiner) + "\n" + choice(second) + choice(endpunct)  + "\n" + "------------"
#         + "\n"  )
