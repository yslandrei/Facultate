# Să se determine al k-lea cel mai mare element al unui șir 
# de numere cu n elemente (k < n). De ex. al 2-lea cel mai mare element din șirul [7,4,6,3,9,1] este 7.

import heapq

# O(n)
def prob7(nums: list[int], k: int) -> int:
  heap = []
  heap = nums[:k]
  heapq.heapify(heap)
  for num in nums[k:]:
    if num > heap[0]:
      heapq.heappop(heap)
      heapq.heappush(heap, num)

  return heap[0]

# O(nlogn)
def prob7_b(nums: list[int], k: int) -> int:
  return sorted(nums, reverse=True)[k - 1]

assert prob7([7,4,6,3,9,1], 2) == 7
assert prob7_b([7,4,6,3,9,1], 2) == 7