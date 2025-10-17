# File Tree Walk (nftw) Utility

A comprehensive C program that implements various file system operations using the `nftw` (new file tree walk) function. This utility provides powerful file and directory manipulation capabilities with support for recursive operations.

## Features

### Basic File Operations
1. **List Files** (`-dirlist`)
   - Lists files in the specified directory (no subdirectories)
   - Sorts files by creation time in reverse order
   - Displays file paths with timestamps

2. **Count Files** (`-countfd`)
   - Counts total number of files in the specified directory
   - Excludes subdirectories from count

3. **Count Files by Type** (`-countype`)
   - Counts files of a specific type/extension
   - Works in the current directory level only

4. **Search Files** (`-filesrch`)
   - Searches for files with exact name match
   - Returns all matching file paths

### Directory Operations
5. **List Subdirectories** (`-dirlst`)
   - Lists all subdirectories with a specific name
   - Shows complete paths to matching directories

6. **Count All Files** (`-fcountrt`)
   - Recursively counts all files
   - Includes files in subdirectories

7. **Count All Directories** (`-dircnt`)
   - Counts total number of directories
   - Includes all subdirectories

### File System Analysis
8. **Calculate Total Size** (`-sumfilesize`)
   - Calculates sum of all file sizes
   - Reports total size in bytes

9. **List Everything** (`-rootlist`)
   - Lists all files and directories
   - Shows complete paths for each entry

10. **List by Extension** (`-Listextn`)
    - Lists all files with specific extension
    - Shows file names and complete paths

### Directory Management
11. **Copy Directory** (`-copyd`)
    - Recursively copies directory structure
    - Preserves file contents and permissions
    - Creates destination directory if needed

12. **Move Directory** (`-dmove`)
    - Moves entire directory structure
    - Preserves file hierarchy
    - Removes source after successful move

13. **Delete by Extension** (`-remd`)
    - Deletes all files with specific extension
    - Works recursively through directories

## Usage

```bash
./a125f <command> [args]
```

### Command Format:
- Basic operations: `./a125f <command> <directory_path>`
- Type/extension operations: `./a125f <command> <type/extension> <directory_path>`
- Copy/Move operations: `./a125f <command> <source_path> <destination_path>`

### Examples:
```bash
# List files in current directory
./a125f -dirlist .

# Count files with .txt extension
./a125f -countype .txt /path/to/dir

# Copy directory
./a125f -copyd /source/dir /dest/dir

# Delete all .tmp files
./a125f -remd /path/to/dir .tmp
```

## Project Structure

```
.
├── a1_Jill_Patel_110176154.c     # Main source code
├── test/                         # Test directory structure
│   ├── 1.txt                     # Test files
│   ├── 2.txt
│   ├── 3.docx
│   └── ...                       # Nested test directories
└── test.txt                      # Testing Environment
```

## Technical Implementation

### Key Features
- Uses POSIX-compliant `nftw` function
- Supports recursive directory traversal
- Implements efficient file operations
- Handles file permissions properly
- Includes error handling for all operations

### Dependencies
- POSIX-compliant system
- C Standard Library
- `nftw` library support
- GNU extensions (for advanced features)

### Compilation
```bash
gcc -o a125f a1_Jill_Patel_110176154.c
```

## Test Directory Structure
The project includes a comprehensive test directory structure to validate various operations:

```
test/
├── 1.txt, 2.txt, 3.docx        # Various file types
├── 1/                          # Nested directories
│   ├── 1.txt, 2.txt
│   ├── 1/
│   │   └── 1.txt
│   └── 2/
│       └── 1.txt
├── 2/
│   └── 1.txt
└── 3/, 4/                      # Empty directories
```

This structure helps test:
- File operations at different directory depths
- Handling of various file types
- Directory creation and deletion
- Recursive operations
- Edge cases in file system traversal

## Error Handling
- Validates command-line arguments
- Checks for file/directory permissions
- Handles path length limitations
- Provides meaningful error messages
- Prevents buffer overflows
- Implements array bounds checking