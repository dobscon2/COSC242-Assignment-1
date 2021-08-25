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

### Linear Probing

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

### Double Hashing

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