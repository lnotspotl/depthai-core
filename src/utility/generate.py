import os

def generate_identity_files(n: int):
    root_dir = os.path.dirname(os.path.abspath(__file__))

    # Generate identity.hpp - declarations
    with open(os.path.join(root_dir, "identity.hpp"), "w") as hpp:
        hpp.write("#pragma once\n\n")
        for i in range(n):
            hpp.write(f"int identity{i}(int x);\n")

    # Generate identity.cpp - definitions
    with open(os.path.join(root_dir, "identity.cpp"), "w") as cpp:
        cpp.write('#include "identity.hpp"\n\n')
        for i in range(n):
            cpp.write(f"int identity{i}(int x) {{\n")
            cpp.write("    return x;\n")
            cpp.write("}\n\n")


# Example usage:
if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("n", type=int)
    args = parser.parse_args()
    generate_identity_files(args.n)