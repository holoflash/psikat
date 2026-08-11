Broke out the pen and paper and found some interesting number relationships.
Specifically for traversing between the various subdivisions algorithmically.
It seems that adding 5 and 7 based subdivisions to psikat can yield some very interesting benefits.

I'm probably totally re-inventing the wheel here on some very basic mathematical concept,
but I'm not searching for it online because I'm enjoying creating my own intuitive understanding.

|     |     |     |     |     |
| --- | --- | --- | --- | --- |
| 4   | 5   | 6   | 7   | 2^0 |
| 8   | 10  | 12  | 14  | 2^1 |
| 16  | 20  | 24  | 28  | 2^2 |
| 32  | 40  | 48  | 56  | 2^3 |
| 64  | 80  | 96  | 112 | 2^4 |
| 128 | 160 | 192 | 224 | 2^5 |
| 256 | 320 | 384 | 448 | 2^6 |
| 512 | 640 | 768 | 896 | 2^7 |

> The right-most column indicates the distance between the numbers on that row

---

**To traverse up or down the same column:**
_Meaning: go to the next/prev step in this subdivision series_

x= **current_number**
up= x * 2
down= x / 2

**To go to next or previous row:**
_Meaning: while knowing which subdivision series we're in, go to closest new/prev subdivision_

y= **subdivision_series**  
x= **current_number**  
next= x + ( x / y )
prev= x - ( x / y )

---

If we're at the edge of a column, the above algorithm loops over to the next/previous row.
That means that these numbers could be placed in one row. Let's see what relationship emerges between them.
The **subdivision_series** parameter is not sustainable.

+1 [4 5 6 7 8] +2 [10 12 14 16] +4 [20 24 28 32] +8 [40 48 56 64] +16 [80 96 112 128] +32 [160 192 224 256]

The goal is to find a function that can allow us to go up or down from any of the numbers without knowing anything else.
Honestly, in the program I could just put these numbers in an array and index++ to go to the next subdivision.
But something tells me that figuring this out will be useful.

How can we know which **subdivision_series** we're currently in just by looking at the x value.

x=24 (belongs to **6** series)
y=x/2/2 y=x/4 = **6**

x=112 (belongs to **7** series)
y=x/2/2/2/2 y=x/16 = **7**

next= 112 + ( 112 / 7 ) = 128

Ok, I felt like I was losing my mind a bit and searched online how to figure out the number of divisions needed
to reach the **base** number. Seems like I was looking for a logarithm!
What a feat it will be if I can pull off this project of with my level of maths knowledge.

**Our base number y must be 4 <= y <8 [4,5,6,7] aka. 2^2 <= y < 2^3**

Using a base 2 logarithm we can find how many increments of 2^n we are away from the base.

log2(16) = 2 * 2 * 2 * 2 = 2^4 = 4

For x=80
[log2(80)] = 6

Sooo, to GET to the bracket that **80** sits in, we doubled **6** times from it's base!
Now, we just need to un-double 6 times and we should find the base!
But, if we undouble 6 times:
80/2/2/2/2/2/2 = 1.25 -> we'll go beyond our base! which is **4 <= y <8**
Undouble 5 times:
80/2/2/2/2/2 = 2.5 -> nope
80/2/2/2/2 = 5 -> BINGO!

So. if we look at this again:
x=112 (belongs to **7** series)
y=x/2/2/2/2 y=x/16 = **7**
We're actually missing a variable here and it is the number of divisions.

next= x + ( x / y )
y= x / z
z= 2 ^ ([log2(x)]-2) [ ]:indicates rounding down
Let's try!

y = 24 / z
z= 2 ^ ( 4 - 2) = 4
y= 24 / 4 = 6
next= 24 + (24 / 6) = 28

**BOOOOOM!!!!**

And in javascript:

```js
function next_number(curr) {
  const y = curr / 2 ** (Math.floor(Math.log2(curr)) - 2);
  const next = curr + curr / y;
  return next;
}
```

What a beauty!

y = x / z
z = 2 ^ ( [log2(x)] -2 )

next_number = x + (x / y);

TODO: Need to think again!
This doesn't work across boundaries!!
previous_number = x - (x / y);
