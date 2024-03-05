# Pentru un șir cu n elemente care conține valori din mulțimea {1, 2, ..., n - 1} astfel încât 
# o singură valoare se repetă de două ori,  să se identifice acea valoare care se repetă. De ex. în șirul [1,2,3,4,2]
# valoarea 2 apare de două ori.

# O(n)
def prob5(nums: list[int]) -> int:
  sum = 0
  for i in range(len(nums)):
    sum = sum + nums[i] - i
  return sum

# O(n)
def prob5_b(nums: list[int]) -> int:
  numSet = set()
  for num in nums:
    if num in numSet:
      return num
    numSet.add(num)

assert prob5([1,2,3,4,2]) == 2
assert prob5_b([1,2,3,4,2]) == 2