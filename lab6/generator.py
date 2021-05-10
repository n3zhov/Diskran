import random
import sys


def bin_pow(a, b):
    if b == 0:
        return 1
    elif b % 2 == 0:
        return bin_pow(a, b // 2) * bin_pow(a, b // 2)
    else:
        return bin_pow(a, b - 1) * a


if __name__ == "__main__":
    actions = ["+", "-", "*", "/", "^", "<", ">", "="]
    count_of_tests = int(sys.argv[1]) + 1
    for enum in range(1, count_of_tests):
        keys = dict()
        test_file_name = "tests/{:02d}".format(enum)
        with open("{0}.t".format(test_file_name), 'w') as output_file, \
                open("{0}.a".format(test_file_name), "w") as answer_file:

            num_of_req = 10 ** enum
            for _ in range(num_of_req):
                action = random.choice(actions)
                lhs = random.randint(0, 10000000)
                if action == "^":
                    rhs = random.randint(0, 100)
                else:
                    rhs = random.randint(0, 10000000)
                output_file.write("{0} {1} {2}\n".format(lhs, rhs, action))
                if action == "+":
                    res = lhs + rhs
                    answer_file.write("{0}\n".format(res))

                elif action == "-":
                    if lhs < rhs:
                        answer_file.write("Error\n")
                    else:
                        res = lhs - rhs
                        answer_file.write("{0}\n".format(res))

                elif action == "*":
                    res = lhs * rhs
                    answer_file.write("{0}\n".format(res))

                elif action == "/":
                    if rhs == 0:
                        answer_file.write("Error\n")
                    else:
                        res = lhs // rhs
                        answer_file.write("{0}\n".format(res))

                elif action == "^":
                    res = bin_pow(lhs, rhs)
                    answer_file.write("{0}\n".format(res))

                elif action == "<":
                    if lhs < rhs:
                        answer_file.write("true\n")
                    else:
                        answer_file.write("false\n")

                elif action == ">":
                    if lhs > rhs:
                        answer_file.write("true\n")
                    else:
                        answer_file.write("false\n")

                elif action == "=":
                    if lhs == rhs:
                        answer_file.write("true\n")
                    else:
                        answer_file.write("false\n")
