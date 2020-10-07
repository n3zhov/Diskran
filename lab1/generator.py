import sys
import random
import string

TEST_COUNT = 7

def randhex(size):
    result = ""
    for i in range(size):
        result += str(random.choice("0123456789abcdef"))
    return result

def randvalue():
    result = ""
    size = random.randint(1, 2048)
    for i in range(size):
        result += random.choice(string.ascii_letters)
    return result

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    lines = []
    lines.extend([10 ** i for i in range(TEST_COUNT)])

    for enum, test_count in enumerate(range(1, TEST_COUNT + 1)):
        test = []

        line_count = lines[enum]
        for _ in range(line_count):
            key = randhex(32)
            value = randvalue()
            test.append((key, value))

        test_name = "{}/{:02d}".format(test_dir, test_count)
        with open(f'{test_name}.t', 'w') as ftest:
            for key, value in test:
                ftest.write(f'{key} {value}\n')

        answer = sorted(test, key=lambda x: x[0])
        with open(f'{test_name}.a', 'w') as ftest:
            for key, value in answer:
                ftest.write(f'{key} {value}\n')


main()
