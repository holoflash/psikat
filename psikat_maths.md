Broke out the pen and paper and found some interesting number relationships.
Specifically for traversing between the various subdivisions algorithmically.
It seems that adding 5 and 7 based subdivisions to psikat can yield some very interesting benefits.

I'm probably totally re-inventing the wheel here on some very basic mathematical concept,
but I'm not searching for it online because I'm enjoying creating my own intuitive understanding.

| x^2 | x^2 | x^2 | x^2 | x^2  |
| --- | --- | --- | --- | ---- |
| 4   | 5   | 6   | 7   | +1   |
| 8   | 10  | 12  | 14  | +2   |
| 16  | 20  | 24  | 28  | +4   |
| 32  | 40  | 48  | 56  | +8   |
| 64  | 80  | 96  | 112 | +16  |
| 128 | 160 | 192 | 224 | +32  |
| 256 | 320 | 384 | 448 | +64  |
| 512 | 640 | 768 | 896 | +128 |

> The right-most column indicates the distance between the numbers on that row
> The top row shows how the distance between numbers in the column is x^2

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
24/2=12 12/2=**6**
y=x/2/2 y=x/4

x=112 (belongs to **7** series)
112/2=56 56/2=28 28/2=14 14/2=**7**
y=x/2/2/2/2 y=x/16

Ok, but the number of times we need to divide is still unknown.
Can it be a multiplication instead?
Basically given a number x:(eg. 24) I want to find out y:(eg. 6)
On the way there, if we can find z:(eg. 16) it can help us get to y.
