
# coding: utf-8

# In[4]:


from random import choice


# In[8]:


first = ["Stop", "Oppose", "Support", "Arrested", "Strike", "Slips", "Arbitrate", "Perish"]
joiner = ["The", "--", "Some", "A", "All", "Minor", "", "Horrid", "Sleek"]
second = ["Troop", "Troops", "War", "Wars", "President", "Presidents", "Footmen", "Footman", "Marauder", "Marauders", "Abortion", "Abortions"]
punct = [",", ".", "--", ";"]
endpunct = [".", "!", ""]


# In[6]:


for items in range(10):
    print(choice(first) or choice(joiner))


# In[10]:


for items in range(50):
    print ("------------" + "\n" + choice(first) + "\n" + choice(joiner) + "\n" + choice(second) + choice(endpunct)  + "\n" + "------------"
        + "\n"  )

