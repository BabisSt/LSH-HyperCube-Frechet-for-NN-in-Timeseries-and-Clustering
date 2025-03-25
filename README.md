# Finding Nearest Neighbor/s in TimeSeries with Locality Sensitive Hashing, HyperCube, Discrete, and Continuous Frechet

**Data Clustering - Second Project for Software Development for Algorithmic Problems**

This project utilizes algorithms such as Locality Sensitive Hashing (LSH), HyperCube (for the first exercise), and Discrete and Continuous Frechet to find the nearest neighbor (NN) in TimeSeries with L2 distance metric.

- Plotted results to visualize the data.
- Reduced complexity by filtering and removing the time dimension.
- Applied Discrete and Continuous Frechet between TimeSeries.
- Implemented K-means++, Lloyd's algorithm, and assignment by Range Search (LSH Frechet / LSH Vector / HyperCube).

**Note**: Not fully functional.

---

## Project Details

**Author**: Stevis Charalampos - Antonios (sdi1600278)

### Directory Structure:

- **assets**: Contains dataset and query files.
- **bin**: Contains executable files.
- **build**: Contains `.o` object files.
- **include**: Contains header files (`.h` and `.hpp`).
- **logs**: Contains `logs.txt`, which stores the output and logs of the project.
- **src**: Contains source code files (`.cpp`).
- **cluster.conf**: Configuration file.
- **Makefile**: Build configuration file.
- **README**: This documentation.

### How to Run:

After building the project with `make`, there are two ways to run the program:

1. **Manual Run**:
   - Navigate to the `bin` directory.
   - Execute commands as outlined in the project specifications.
   
2. **Predefined Run**:
   - Run predefined commands from the `Makefile`, such as `run-lsh`, `run-hc`, etc.
   - Some commands may not require all arguments, in which case default values are used.

If you choose the first option, the program will ask for input files (dataset and queries). If the second option is chosen, the program runs automatically using the files specified in the `Makefile`. After execution, the program allows you to rerun with different data.

The results are logged in `logs/logs.txt`.

### Functionality of the Project:

The program reads and stores datasets for both input and queries. It operates in cluster mode if enabled, and performs the following operations:

- **LSH**: Finds nearest neighbors using brute force or by getting closest neighbors with hash tables.
- **Hypercube**: In addition to LSH, it calculates the Hamming distances and generates the `f` values.
- **Frechet**: Applies the discrete and continuous Frechet distances between TimeSeries. In discrete Frechet, curves are snapped according to the given delta, and duplicate entries are filtered using the `Min_max_filter` method. Padding is applied to make the curves equal in size.

The project computes the hash functions for hash tables and organizes them into buckets for further queries.

### What the Project Can Do:

- Reads datasets and queries, storing them appropriately.
- Works in both cluster mode and non-cluster mode, performing operations like LSH, Hypercube, and Frechet.
- **LSH** finds times and makes necessary prints using both brute force and closest neighbor search.
- **Hypercube** computes the Hamming distance and generates additional values.
- **Frechet** snaps curves and removes duplicates, applying padding for equal curve sizes. It integrates Frechet into the LSH operations.

For the clustering part, the program runs algorithms like **Lloyd's**, **LSH with Frechet**, and others using the `run-cluster-...` commands.

### Known Limitations:

- **Continuous Frechet**: The program currently does not support Continuous Frechet as we were unable to integrate the required library.


