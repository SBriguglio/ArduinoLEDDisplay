# Experiments

For now, I will catalogue all of my experimental files here, if I find they are worth documenting. I would like to keep some notes/updates on this document as well.

## Entry: 16/04/22

Just learning how the WS2812B matrix works was interesting. I started off "drawing" a bug that iterates over the leds in the matrix which is represented as an array in the code. This representation is not as easy to work with, and I am avoiding more high-level functions from other libraries so that I can better understand some of the mechnics better. 

I've completed my first experiments,  ```FirstLED.ino```, and made a function that draws a square onto the matrix. It should work with any size matrix with the same wiring pattern as mine. I've tested it on 8x8, 16x16 and 8x32 matricies. I am certain that I am certain I have taken the naive approach to this and once exams are finized I think I should research rasterization (if that is the correct term for what I am thinking of).

