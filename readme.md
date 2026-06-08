# Job Filer

Job Filer is a small C script project that helps organize resume files after I download them.

Right now, the program scans my Downloads folder for files named like:

```text
Ronny_Toribio_Resume_<company>.pdf
```

When it finds one, it creates a folder for the company inside my resumes directory, moves the file there, and renames it to:

```text
Ronny Toribio Resume.pdf
```

## What I Am Practicing

This project is mainly for learning and practicing C basics with real file-system work:

- Reading files from a directory with `opendir()` and `readdir()`
- Searching filenames with string functions like `strstr()`
- Creating directories with `mkdir()`
- Moving and renaming files with `rename()`
- Building file paths with character arrays and `snprintf()`
- Working with loops, conditionals, and basic string manipulation

## Project Structure

```text
.
├── Makefile
├── src/
│   └── main.c
└── bin/
    └── filer
```

## How To Run

Build and run the program with:

```sh
make
```

The current paths are hardcoded in `src/main.c`, so the script is set up for my local machine.

## Current Limitations

- Only resume files are handled right now.
- The Downloads and resume output folders are hardcoded.
- The filename parsing depends on the current naming pattern.
- It uses fixed-size character arrays instead of dynamically allocated memory.

## Future Improvements

Later I want to add:

- Cover letter support, so matching cover letters can be filed with each resume
- Dynamic memory allocation with `malloc()` instead of relying only on fixed-size arrays
- More flexible folder and filename handling
- Better error handling when folders already exist or files fail to move
