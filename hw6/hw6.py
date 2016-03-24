## list-1
def sum3(nums):
  return sum(nums)

def max_end3(nums):
    return [max(nums[0],nums[2])] + [max(nums[0],nums[2])] + [max(nums[0],nums[2])]

def make_ends(nums):
    i = len(nums)
    return[nums[0]] + [nums[i-1]]
  
def rotate_left3(nums):
  return nums[1:] + nums[0:1]

def has23(nums):
  return 2 in nums or 3 in nums

## list-2

def count_evens(nums):
  count = 0
  for num in nums:
    if num % 2 == 0:
      count = count + 1
  return count
    
def big_diff(nums):
  return max(nums) - min(nums)

def centered_average(nums):
  a1 = sum(nums) - max(nums) - min(nums)
  a2 = len(nums) - 2
  return a1/a2

def sum13(nums):
        acc = 0
        i = 0
        l = len(nums)
        for num in nums:
                i = i + 1
                if i == l:
                    if nums[-1] == 13:
                       return acc
                    else: 
                       return acc + nums[-1]
                if num == 13:
                    if nums[i] == 13:
                       acc = acc + 0
                    else:
                       acc = acc - nums[i]
                else:
                        acc = num + acc
        return acc
    
def sum67(nums):
    switch = 0
    sum = 0
    for num in nums:
      if switch == 1:
         if num == 7:
          switch = 0         
          sum = sum - 7
         else:
          sum = sum + 0
      if num == 6:
         switch = 1
      if switch == 0: 
          sum = sum + num
    return sum
      
def has22(nums):
 res = False
 i = 1
 for num in nums:
   if i == len(nums):
     break
   if num == 2:
     if nums[i] == 2:
      return True
     else:
      i = i + 1
   if num != 2:
      i = i + 1
 return res

##String-1
def extra_end(str):
  return str[-2:] + str[-2:] + str[-2:]

def without_end(str):
  return str[1:-1]


##String-2
def double_char(str):
  r = ''
  for i in range(len(str)):
   r = r + str[i] + str[i]
  return r

def count_hi(str):
  ran = len(str) - 1
  con = 0
  for i in range (len(str)):
    if i + 1 > ran:
      return con
    if str[i] == 'h'and str[i+1] == 'i':
      con = con + 1
    else:
      con = con + 0 
  
  return con

def cat_dog(str):
  d = 0
  c = 0
  for i in range (len(str) -2):
    if str[i:i+3] == 'dog':
      d = d + 1
    if str[i:i+3] == 'cat':
      c = c + 1
    else : 
      c = c + 0
      
  return d == c 
      

def count_code(str):
  ran = len(str) - 1
  con = 0
  for i in range (len(str)):
    if i + 3 > ran:
      return con
    if str[i] == 'c'and str[i+1] == 'o' and str[i+3] == 'e':
      con = con + 1
    else:
      con = con + 0 
  
  return con

def end_other(a, b):
  a1 = a.lower()
  b1 = b.lower()
  return a1.endswith(b1) or b1.endswith(a1)

def xyz_there(str):
  sum = False
  for i in range (len(str) - 2):
    if i == 0 and str[i:i+3] == 'xyz':
     return True
    if str[i-1] != '.' and str[i:i+3] == 'xyz':
     return True
    else:
     sum = False
  return sum

## count space

def count1(str):
	l = len(str.split("\n"))
	w = len(str.split(" "))
	c = len(str)
	return [l,w,c]

count1("The quick brown fox jumped over the lazy dog.")

def count2(str):
	r = [str.count(c) for c in "0123456789" ]
	space = sum([str.count(c) for c in " \t\n" ])
	chars = len(str) - sum(r) - space
	r.append(space)
	r.append(chars)
	return r

count2("The 25 quick brown foxes jumped over the 27 lazy dogs 17 times.\n")
      





    
