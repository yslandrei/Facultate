# Să se determine cuvintele unui text care apar exact o singură dată în acel text. 
# De ex. cuvintele care apar o singură dată în ”ana are ana are mere rosii ana" sunt: 'mere' și 'rosii'.

# O(n)
def prob4(s: str) -> list[str]:
    wordMap = dict()
    for word in s.split(" "):
      wordMap[word] = wordMap.get(word, 0) + 1
    words = []
    for word in wordMap:
      if wordMap[word] == 1:
        words.append(word)
    return words

assert prob4("ana are ana are mere rosii ana") == ['mere', 'rosii']

    