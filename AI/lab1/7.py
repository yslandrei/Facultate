# Să se determine al k-lea cel mai mare element al unui șir 
# de numere cu n elemente (k < n). De ex. al 2-lea cel mai mare element din șirul [7,4,6,3,9,1] este 7.

import heapq

def prob7(nums: list[int], k: int) -> int:
  heap = []
  for num in nums:
    heapq.heappush(heap, -num)
    if len(heap) > k:
      heapq.heappop(heap)

  return heap[0]