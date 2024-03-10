class Solution:
    def longestPalindrome(self, s: str) -> str:
        dp = [[0 for _ in range(len(s))] for _ in range(len(s))]
        for i in range(len(s)):
            dp[i][i] = 1

        for leng in range(2, len(s) + 1):
            for i in range(len(s) - leng + 1):
                j = i + leng - 1
                if leng == 2 and s[i] == s[j]:
                    dp[i][j] = 2
                elif s[i] == s[j] and dp[i + 1][j - 1] != 0:
                    dp[i][j] = dp[i + 1][j - 1] + 2

        return max([max(row) for row in dp])       


print(Solution().longestPalindrome("babad"))  # 5