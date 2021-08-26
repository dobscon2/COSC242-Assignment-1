# COSC242 - Assignment 1 

## Group members
* Connor Dobson - dobco402
* Hayden Knox - hnoha805
* Eddie Finlayson - fined080

## Findings

Throughout our testing with different data double hashing has consistently provided better hashing results than linear probing.

Using double hashing compared to linear probing has resulted in less collisions, especially when the hash table is above 60% full

## Evidence

The following tables were using the war-and-peace-20.txt file located in the coursework folder.

The following tables below have a hash table capacity of 113

### Linear Probing - Hash Table Capacity 113

| Percent Full | Current Entries | Percent At Home | Average Collisions | Maximum Collisions |
| ------------ | --------------- | --------------- | ------------------ | ------------------ |
| 10           | 11              | 90.9            | 0.09               | 1                  |
| 20           | 22              | 86.4            | 0.14               | 1                  |
| 30           | 33              | 75.8            | 0.36               | 4                  |
| 40           | 45              | 71.1            | 0.40               | 4                  |
| 50           | 56              | 69.6            | 0.46               | 4                  |
| 60           | 67              | 65.7            | 0.60               | 4                  |
| 70           | 79              | 57.0            | 1.20               | 14                 |
| 80           | 90              | 53.3            | 1.68               | 17                 |
| 90           | 101             | 49.5            | 3.03               | 42                 |
| 100          | 113             | 46.0            | 6.60               | 107                |

### Double Hashing - Hash Table Capacity 113

| Percent Full | Current Entries | Percent At Home | Average Collisions | Maximum Collisions |
| ------------ | --------------- | --------------- | ------------------ | ------------------ |
| 10           | 11              | 81.8            | 0.18               | 1                  |
| 20           | 22              | 81.8            | 0.18               | 1                  |
| 30           | 33              | 69.7            | 0.36               | 3                  |
| 40           | 45              | 66.7            | 0.42               | 3                  |
| 50           | 56              | 62.5            | 0.45               | 3                  |
| 60           | 67              | 62.7            | 0.49               | 3                  |
| 70           | 79              | 57.0            | 0.67               | 4                  |
| 80           | 90              | 53.3            | 0.82               | 9                  |
| 90           | 101             | 49.5            | 1.12               | 9                  |
| 100          | 113             | 46.0            | 2.99               | 58                 |

The following tables below have a hash table capacity of 1109

### Linear Probing - Hash Table Capacity 1109

| Percent Full | Current Entries | Percent At Home | Average Collisions | Maximum Collisions |
| ------------ | --------------- | --------------- | ------------------ | ------------------ |
| 10           | 100             | 90.0            | 0.12               | 2                  |
| 20           | 201             | 89.6            | 0.14               | 3                  |
| 30           | 302             | 85.1            | 0.20               | 3                  |
| 40           | 403             | 79.2            | 0.32               | 5                  |
| 50           | 504             | 73.6            | 0.46               | 8                  |
| 60           | 605             | 69.8            | 0.69               | 24                 |
| 70           | 706             | 65.0            | 1.02               | 25                 |
| 80           | 807             | 59.5            | 1.76               | 46                 |
| 90           | 908             | 54.7            | 3.59               | 135                |
| 100          | 1009            | 49.8            | 14.22              | 954                |

### Double Hashing - Hash Table Capacity 1109

| Percent Full | Current Entries | Percent At Home | Average Collisions | Maximum Collisions |
| ------------ | --------------- | --------------- | ------------------ | ------------------ |
| 10           | 100             | 92.0            | 0.08               | 1                  |
| 20           | 201             | 90.5            | 0.10               | 2                  |
| 30           | 302             | 86.1            | 0.17               | 2                  |
| 40           | 403             | 80.4            | 0.27               | 4                  |
| 50           | 504             | 74.4            | 0.37               | 4                  |
| 60           | 605             | 71.4            | 0.50               | 11                 |
| 70           | 706             | 66.7            | 0.71               | 14                 |
| 80           | 807             | 61.0            | 1.06               | 14                 |
| 90           | 908             | 56.6            | 1.52               | 48                 |
| 100          | 1009            | 51.2            | 5.91               | 744                |