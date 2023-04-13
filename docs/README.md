# Class of Life Command Line Interface (CoL CLI)

## Examples

You can find some example commands at [`examples`](examples) and some sample data files at [`examples/data`](examples/data).

## Reference

### Run

Run the commands inside a file:

    run PATH_TO_FILE

### Add

Adds a new object:

    add genome -id ID -rna RNA_STRAND -dna FIRST_STRAND SECOND_STRAND
    add chromosome -to [cell/animal] -id PARENT_ID -dna FIRST_STRAND SECOND_STRAND
    add cell -id ID -number NUMBER_OF_CHROMOSOMES
    add animal -id ID -number NUMBER_OF_CHROMOSOMES
    add virus -id ID -rna RNA_STRAND

### Load

Reads a `FastA` file and parses its content:

    load genomes -from PATH_TO_FILE
    load cells -from PATH_TO_FILE
    load animals -from PATH_TO_FILE
    load viruses -from PATH_TO_FILE

Note: The header of each record in a `FastA` file must follow a specific pattern. Please take a look at [`examples/data`](examples/data) to find out how to feed records into the program.

### Delete

### Show

### List

### Genomes

### Cells

### Animals

### Viruses

### Clear

### Exit

### About

### Help