from collections import Counter, deque


def min_permute_characters(s1, target):
    s2 = deque(target)
    count = 0
    for i in range(len(s1)):
        if s1[i] != s2[0]:
            count += 1
        else:
            s2.popleft()
    return count

def generatePalindromes(s):
  def dfs(palindrome_half):
      if len(palindrome_half) == len(s):
          palindromes.append(palindrome_half)
          return
      for char, count in char_count.items():
          if count > 1:
              char_count[char] -= 2
              dfs(char + palindrome_half + char)
              char_count[char] += 2

  char_count = Counter(s)
  middle_char = ''
  for char, count in char_count.items():
      if count % 2 != 0:
          if middle_char:
              return []
          middle_char = char
          char_count[char] -= 1

  palindromes = []
  dfs(middle_char)
  return palindromes

s = "abcdcdab"
minn = float('inf')
for pal in generatePalindromes(s):
    minn = min(min_permute_characters(s, pal), minn)

print(minn)

def is_palindrome(s):
    return s == s[::-1]

def canBePalindrome(s):
    return sum(1 for count in Counter(s).values() if count % 2) <= 1

print(is_palindrome("abcdcdab")) # True