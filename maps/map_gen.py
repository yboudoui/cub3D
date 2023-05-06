import random

def create_map(width, height):
    return [['1' for _ in range(width)] for _ in range(height)]

def is_valid_move(x, y, width, height):
    return x > 0 and x < width - 1 and y > 0 and y < height - 1

def generate_map(width, height, iterations):
    map = create_map(width, height)

    x, y = width // 2, height // 2
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    for _ in range(iterations):
        dx, dy = random.choice(directions)
        if is_valid_move(x + dx, y + dy, width, height):
            x += dx
            y += dy
            map[y][x] = '0'

    map[y][x] = 'N'
    return map

def print_map(map):
    for row in map:
        print(''.join(row))

width, height = 21, 21
iterations = 500
map = generate_map(width, height, iterations)
print_map(map)
