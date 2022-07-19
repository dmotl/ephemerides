import sys, os

def hip_reduce(main_file, reduced_file):
    out = []
    header = 1
    with open(main_file, "r") as f:
        lines = f.readlines()
        for line in lines:
            try:
                hip = line[0:6].strip()
                hd = line[359:365].strip()
                if len(hd) > 0:
                    out.append(hip + "=" + hd)
            except:
                print("Error in line: " + line)

    with open(reduced_file, "w") as f:
        for line in out:
            f.write(line + "\n")

if __name__ == '__main__':
    hip_reduce("main", "hip2hd")
