# Pentru un șir cu n numere întregi care conține și duplicate, să se determine elementul 
# majoritar (care apare de mai mult de n / 2 ori). 
# De ex. 2 este elementul majoritar în șirul [2,8,7,2,2,5,2,3,1,2,2].

# O(n)
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
    for num in nums:
      if candidate == num:
        count += 1

    if count > len(nums) // 2:
        return candidate
    
# O(n)
def prob6_b(nums: list[int]) -> int:
  numMap = {}
  for num in nums:
    if num in numMap:
      numMap[num] += 1
    else:
      numMap[num] = 1

  for num in numMap:
    if numMap[num] > len(nums) // 2:
      return num
    
assert prob6([2,8,7,2,2,5,2,3,1,2,2]) == 2
assert prob6_b([2,8,7,2,2,5,2,3,1,2,2]) == 2