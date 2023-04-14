# Documentation

## Examples

You can find some sample commands at [`examples`](/examples) and some sample data files at [`examples/data`](/examples/data).

## Reference

### Run

Run the commands inside a file:

    run PATH_TO_FILE

### Add

Add a new object to the workspace:

    add genome -id ID -rna RNA_STRAND -dna FIRST_STRAND SECOND_STRAND
    add chromosome -to [cell/animal] -id PARENT_ID -dna FIRST_STRAND SECOND_STRAND
    add cell -id ID -number NUMBER_OF_CHROMOSOMES
    add animal -id ID -number NUMBER_OF_CHROMOSOMES
    add virus -id ID -rna RNA_STRAND

### Load

Parse a `FastA` file and add its records to the workspace:

    load genomes -from PATH_TO_FILE
    load cells -from PATH_TO_FILE
    load animals -from PATH_TO_FILE
    load viruses -from PATH_TO_FILE

Note: The header of each record in a `FastA` file must follow a specific pattern. Please take a look at [`examples/data`](/examples/data) to find out how to feed records into the program.

### Delete

Delete an object from the workspace:

    delete genome -id ID
    delete chromosome -from [cell/animal] -id PARENT_ID -index INDEX
    delete cell -id ID
    delete animal -id ID
    delete virus -id ID

### Show

Show an existing object:

    show genome -id ID
    show chromosome -from [cell/animal] -id ID -index INDEX
    show cell -id ID
    show animal -id ID
    show virus -id ID

### List

List all existing objects:
    
    list genomes
    list cells
    list animals
    list viruses

### Genomes

#### Transform

Transform RNA to DNA:

    genomes transform -id ID

#### Mutate

Perform different kinds of mutation:

    genomes mutate rna small -id ID -from SOURCE_NUCLEOTIDE -to DESTINATION_NUCLEOTIDE -number NUMBER_OF_MUTATIONS
    genomes mutate rna large -id ID -from SOURCE_CHUNK -to DESTINATION_CHUNK
    genomes mutate rna inversely -id ID -on TARGET_CHUNK
    genomes mutate dna small -id ID -from SOURCE_NUCLEOTIDE -to DESTINATION_NUCLEOTIDE -number NUMBER_OF_MUTATIONS
    genomes mutate dna large -id ID -from SOURCE_CHUNK -to DESTINATION_CHUNK
    genomes mutate dna inversely -id ID -on TARGET_CHUNK

### Cells

#### Mutate

Perform different kinds of mutation:

    cells mutate small -id ID -chromosome INDEX -from SOURCE_NUCLEOTIDE -to DESTINATION_NUCLEOTIDE -number NUMBER_OF_MUTATIONS
    cells mutate large -id ID -from SOURCE_INDEX SOURCE_CHUNK -to DESTINATION_INDEX DESTINATION_CHUNK
    cells mutate inversely -id ID -on INDEX TARGET_CHUNK

#### Palindromes

List all complementary palindromes within all chromosomes of the cell:

    cells palindromes -id ID

#### Die

Kill the cell if it has abnormal chromosomes:

    cells die -id ID

### Animals

#### Mutate

Perform different kinds of mutation:

    animals mutate small -id ID -chromosome INDEX -from SOURCE_NUCLEOTIDE -to DESTINATION_NUCLEOTIDE -number NUMBER_OF_MUTATIONS
    animals mutate large -id ID -from SOURCE_INDEX SOURCE_CHUNK -to DESTINATION_INDEX DESTINATION_CHUNK
    animals mutate inversely -id ID -on INDEX TARGET_CHUNK

#### Palindromes

List all complementary palindromes within all chromosomes of the animal:

    animals palindromes -id ID

#### Similarity

Compute the similarity score between two animals:

    animals similarity FIRST_ANIMAL_ID SECOND_ANIMAL_ID

#### Equality

Check if two animals are of the same species:

    animals equality FIRST_ANIMAL_ID SECOND_ANIMAL_ID

#### Reproduce

Perform asexual reproduction:

    animals reproduce ANIMAL_ID -id CHILD_ID

Perform sexual reproduction:

    animals reproduce FIRST_ANIMAL_ID SECOND_ANIMAL_ID -id CHILD_ID

#### Kill

Kill abnormal chromosomes:

    animals kill chromosomes -id ID

#### Die

Kill the cell if it has abnormal chromosomes:

    animals die -id ID

### Viruses

#### Mutate

Perform different kinds of mutation:

    viruses mutate small -id ID -from SOURCE_NUCLEOTIDE -to DESTINATION_NUCLEOTIDE -number NUMBER_OF_MUTATIONS
    viruses mutate large -id ID -from SOURCE_CHUNK -to DESTINATION_CHUNK
    viruses mutate inversely -id ID -on TARGET_CHUNK

#### Parthogenicity

Check if a virus is pathogenic for an animal:

    viruses pathogenicity -id VIRUS_ID -for ANIMAL_ID

### More Commands
Clear the screen:

    clear

See the help:

    help

See the about:

    about

Exit the program:

    exit