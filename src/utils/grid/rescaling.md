**Assumptions**

1. At any point in time, a pattern should have at least some cells that are in the current zoom level.
   FALSE: If a pattern is created and scaled to a level incompatible with all current cells,
   none of the cells will be possible to resolve.

**Truths**

1. There may be states where a pattern has ZERO cells in the current zoom level.
2. In _almost all cases_, scaling down will put all scaled down cells into non-editable states.
3. Scaling up will _always_ result in editable states for resolutions from the same _base_ value
4. A decision must bed made whether we should resolve upwards for technically incompatible resolutions.

## Scaling down rules:

**IF the CURRENT value is > 0.5 of the next LOWER value**
We allow the rescale as the granularity can be preserved across rescales.

[x] 1/4 [x] 1/6 -- 1/4 is technically 1.5 1/6s
[ ] 1/4 [ ] 1/6

[x] 1/6 [x] 1/4 -- 1/6 is 0.66 1/4  
[ ] 1/6 [ ] 1/4

---

> When scaling down should be disssalowed

[x] 1/32 [x] 1/16 -- 1/32 is 0.5 1/16  
[ ] 1/32 [ ] 1/16 -- 1/32 can not be expressed in 1/16 values

[x] 1/16 [x] 1/32 -- 1/16 is 2 1/32s  
[ ] 1/16 [x] 1/32

If we were to allow rescale at <= 0.5, we'd lose data on subsequent rescales

## Scaling up rules:

> When scaling up should be disssalowed

[x] 1/4 [x] 1/6 -- Length wise, this looks correct at first glance
[x] 1/4 [x] 1/6 -- But is an illegal move
--------[x] 1/6 -- Here we just made up one extra piece of data

[x] 1/6 [x] 1/4 -- And on the way back with lose one piece of data
[x] 1/6 [x] 1/4
[x] 1/6

## The easy way out?

The easiest solution is to simply not allow any rescales.
But we still need to rescale the grid AND mark where the unresolvable cells are

## The better way

4 5 6 7 8 10 12 14 16 20 24 28 32 40 48 56 64 80 96 112 128

LCM=13440
How many /112s is 5/14s?
X=14
Y=5
Z=112
( ( LCM / x ) * y ) / (LCM / z )
5/14 = 40/112
Doesn't always work though. Same thing but: 5/12s result in non integer value.
Should instead convert to raw LCM values internally:
5/14 = 5* (13440/14) = 4800
Like that, there's zero ambiguity
