import turtle

def draw_spiral(l):
    length = 10

    while length <= 100:
        turtle.forward(length)
        turtle.left(91)
        length = length + 1
    turtle.done()

    return

def hello():
    print('Hello~~~~~~~~~.')