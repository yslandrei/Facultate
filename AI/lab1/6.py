# Pentru un șir cu n numere întregi care conține și duplicate, să se determine elementul 
# majoritar (care apare de mai mult de n / 2 ori). 
# De ex. 2 este elementul majoritar în șirul [2,8,7,2,2,5,2,3,1,2,2].

def prob6(nums: list[int]) -> int:
  candidate = -1
  count = 0
    
  for num in nums:
    if count == 0:
      candidate = num
      count = 1
    elif candidate == num:
      count += 1
    else:
      count -= 1
    count = 0

    count = 0
    for num in nums:
      if candidate == num:
        count += 1

    if count > len(nums) // 2:
        return candidate
    
print(prob6([2,8,7,2,2,5,2,3,1,2,2])) # 2