"""
A nice tool to generate docs for all python utilities that we create.
"""

import argparse
import fnmatch
import os
import re
import subprocess


def create_doc_text(modules):
    """
    Generate the documentation output in markdown
    """

    create_doc_cmd = ["pydocmd", "simple", *modules]
    process = subprocess.Popen(
        create_doc_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

    # Wait for the process to finish.
    exit_status = process.wait()

    # Exit status > 0 == Error
    if exit_status:
        err_msg = process.stderr.read()
        print("Couldn't successfully create the documentation file.")
        print(err_msg)
        raise SystemExit

    # Obtain the markdown string.
    docs = process.stdout.read().decode("utf-8")

    return docs


def create_doc_file(root, docs):
    """
    Write the doc contents to the file.
    """

    # Write the documentation into it's respesctive
    # file.
    with open(f"{root}/docs.md", "w+") as f:
        f.write(docs)


def main(args):
    """
    Walk through the directories of our python project and start
    documenting all of the code.
    """

    if not os.path.exists(f"./{args.directory}"):
        print("The entered directory doesn't exist. Exiting the program.")
        raise SystemExit

    output_md = ["## Documentation"]
    for root, dirs, files in os.walk(f"./{args.directory}"):
        modules = []
        found_file = False
        fixed_root = re.sub("/", ".", re.sub("\./", "", root))

        # Iterate through all of the files and add python modules to the list
        # of modules to be documented
        for file in files:
            if fnmatch.fnmatch(file, "*.py"):
                found_file = True
                removed_ext = re.sub(".py", "", file)
                module_to_document = fixed_root + "." + removed_ext + "++"
                modules.append(module_to_document)

        if found_file:
            print(f"Creating documentation for {root}")
            docs = create_doc_text(modules)
            create_doc_file(root, docs)
            output_md_path = f"* [{fixed_root}]({root}/docs.md)"
            output_md.append(output_md_path)
        else:
            print("No python files found.")

    print("\n---OUTPUT---")
    for md in output_md:
        print(md)


def parse_args():
    """
    Create the argument parser and return the parsed arguments
    """

    parser = argparse.ArgumentParser()

    parser.add_argument(
        "directory",
        type=str,
        help="The directory to traverse. Ideally should be in the same directory as your README.md",
    )

    return parser.parse_args()


if __name__ == "__main__":
    args = parse_args()
    main(args)
