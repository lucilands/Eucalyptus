import os
import sys


def get_linecount(filepath : str, char_to_check_for : str = None, log : bool = False) -> tuple:
    char_count = 0
    if log:
        print("Counting file:", filepath)
    try:
        with open(filepath, "r") as fp:
            for count, line in enumerate(fp):
                if (char_to_check_for != None):
                    if (char_to_check_for in line):
                        char_count += 1
            return (count + 1, char_count + 1)
    except Exception as e:
        print("An error occured while counting file", filepath, ":", e)
        return 0
    

def get_lines_in_directory(dir : str, log_search : bool = False, char_to_check_for : str = None) -> tuple:
    _count = 0
    _char_count = 0
    _files = 0
    _files_ = []
    for root, dirs, files in os.walk(dir, topdown=False):
        for name in files:
            if os.path.isfile(os.path.join(root, name)):
                a, b = get_linecount(os.path.join(root, name), char_to_check_for, log)
                _count += a
                _char_count += b
                _files_.append((os.path.join(root, name), get_linecount(os.path.join(root, name))[0]))
                _files += 1
                if log_search:
                    print("Counted lines in file: ", os.path.join(root, name), "lines in file:", get_linecount(os.path.join(root, name))[0])
        for name in dirs:
            if os.path.isfile(os.path.join(root, name)):
                a, b = get_linecount(os.path.join(root, name), char_to_check_for, log)
                _count += a
                _char_count += b
                _files_.append((os.path.join(root, name), get_linecount(os.path.join(root, name))[0]))
                _files += 1
                if log_search:
                    print("Counted lines in file: ", os.path.join(root, name), "lines in file:", get_linecount(os.path.join(root, name))[0])

    _files_.sort(key = lambda file: -(file[1]))
    return (_count, _files, _files_, _char_count)

if __name__ == "__main__":
    log = False
    podium = False
    check_for_char = None

    if ("-l" in sys.argv or "--log" in sys.argv):
        log = True
    if ("-p" in sys.argv or "--podium" in sys.argv):
        podium = True
    if "-c" in sys.argv:
        check_for_char = sys.argv[sys.argv.index("-c") + 1]
     
    lines, files, file_podium, found_chars = get_lines_in_directory(sys.argv[1], log, check_for_char)
    print("\033[1mTotal lines in", sys.argv[1] + ":\033[0m", lines)
    print("\033[1mAmount of files searched:\033[0m", files)

    if check_for_char != None:
        print("\033[1mAmount of '" + check_for_char + "' in project:\033[0m", found_chars)

    if podium:
        largest_file = file_podium[0]
        smallest_file = file_podium[len(file_podium) - 1]
        print()
        print("\033[1mLargest file:\033[0m", largest_file[0], "with", largest_file[1], "lines")
        print("\033[1mSecond largest file:\033[0m", file_podium[1][0], "with", file_podium[1][1], "lines")
        print("\033[1mThird largest file:\033[0m", file_podium[2][0], "with", file_podium[2][1], "lines")
        print()
        print("\033[1mSmallest file:\033[0m", smallest_file[0], "with", smallest_file[1], "lines")
        print("\033[1mSecond smallest file:\033[0m", file_podium[len(file_podium) - 2][0], "with", file_podium[len(file_podium) - 2][1], "lines")
        print("\033[1mThird smallest file:\033[0m", file_podium[len(file_podium) - 3][0], "with", file_podium[len(file_podium) - 3][1], "lines")
