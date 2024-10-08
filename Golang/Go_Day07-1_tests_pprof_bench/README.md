# Day 07 - Go Boot camp

## Moneybag

This is a pretty well-known problem and your colleague already wrote a code and uploaded it to you for a review:

```
func minCoins(val int, coins []int) []int {
    res := make([]int, 0)
    i := len(coins) - 1
    for i >= 0 {
        for val >= coins[i] {
            val -= coins[i]
            res = append(res, coins[i])
        }
        i -= 1
    }
    return res
}
```

It accepts a necessary amount and a sorted slice of unique denominations of coins. It may be something like [1,5,10,50,100,500,1000] or something exotic, like [1,3,4,7,13,15]. The output is supposed to be a slice of coins of minimal size that can be used to express the value (e.g. for 13 and [1,5,10] it should give you [10,1,1,1]).

The issue is, you have a gut feeling there is something wrong with this code. Your goal here is to write several tests (in `*_test.go` files) for this code, that will show it producing wrong results. Also, you need to write a separate function (you should call it `minCoins2`) which will have the same parameters, but will handle those cases successfully. In case duplicates are present in a slice of denominations or it is not sorted, the function should still give a correct result. In case it is empty, an empty slice should be returned. 

<h2 id="chapter-v" >Chapter V</h2>
<h3 id="ex01">Exercise 01: Need for Speed</h3>

Now as you have new version of code from EX00, let's test it for performance. Your goals here are:

 - get a list of top 10 functions in your code (calling your function with some test data) that your CPU spends the most time executing (you should use Go's builtin tools for that). Submit that list as file `top10.txt`
 
 - write a benchmark version of your tests that will compare the performance of your new code vs. the old one, especially while using relatively big denomination slice. If you find any more optimizations during this phase, feel free to submit newer version of your `minCoins2` function calling it `minCoins2Optimized` (not a required step)

<h2 id="chapter-vi" >Chapter VI</h2>
<h3 id="ex02">Exercise 02: Elder Scrolls</h3>

Now, as you've fixed the bug and wrote some tests for your code, it's time to generate some documentation for it. Describe in comments in your code how is your solution different from the default one and what optimizations did you use. Then, use any tool that you'll manage to find to generate the HTML documentation based on those comments.

Directions on how to reproduce documentation generation should also be included in comments. Saving HTML pages from the web browser is considered cheating (even though not strictly prohibited, so if you couldn't do it any other way just write it explicitly in the comments).

Submit generated documentation (HTML files + static, like images, js and css) packed into a `docs.zip` archive.


